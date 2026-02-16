#include <atomic>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

//   correct using
//   cd /Users/guf/Desktop/Bull-Tech/task4_line_count
//   make
//   ./stress_test.sh
namespace fs = std::filesystem;


static std::uint64_t count_lines_fast(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return 0;

    constexpr std::size_t BUF = 1 << 20; // 1 MiB
    std::vector<char> buf(BUF);

    std::uint64_t lines = 0;
    bool any_read = false;
    char last = 0;

    while (f) {
        f.read(buf.data(), static_cast<std::streamsize>(buf.size()));
        const std::streamsize n = f.gcount();
        if (n <= 0) break;

        any_read = true;
        last = buf[static_cast<std::size_t>(n - 1)];

        const char* b = buf.data();
        const char* e = b + n;
        for (const char* it = b; it != e; ++it) {
            lines += (*it == '\n');
        }
    }

    if (f.bad()) return 0;

    if (any_read && last != '\n') ++lines;
    return lines;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << (argc ? argv[0] : "line_count") << " <directory>\n";
        return 1;
    }

    fs::path dir = argv[1];
    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        std::cerr << "Error: not a directory: " << dir << "\n";
        return 1;
    }

    std::vector<fs::path> files;
    files.reserve(4096);

    for (auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) files.push_back(entry.path());
    }

    const unsigned hw = std::max(1u, std::thread::hardware_concurrency());
    const unsigned workers =
        std::min<unsigned>(hw, files.empty() ? 1u : static_cast<unsigned>(files.size()));

    std::atomic<std::size_t> next{0};
    std::atomic<std::uint64_t> total{0};

    auto worker = [&] {
        std::uint64_t local = 0;
        for (;;) {
            const std::size_t i = next.fetch_add(1, std::memory_order_relaxed);
            if (i >= files.size()) break;
            local += count_lines_fast(files[i]);
        }
        total.fetch_add(local, std::memory_order_relaxed);
    };

    std::vector<std::thread> pool;
    pool.reserve(workers);
    for (unsigned i = 0; i < workers; ++i) pool.emplace_back(worker);
    for (auto& t : pool) t.join();

    std::cout << "Directory   : " << dir << "\n";
    std::cout << "Files scanned: " << files.size() << "\n";
    std::cout << "Cores (hw)   : " << hw << "\n";
    std::cout << "Threads used : " << workers << (workers >= hw && !files.empty() ? "  (tum cekirdekler kullanildi)" : "") << "\n";
    std::cout << "Total lines  : " << total.load(std::memory_order_relaxed) << "\n";

    return 0;
}
