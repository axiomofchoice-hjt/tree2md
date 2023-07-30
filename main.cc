#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::string replace(std::string s, std::string a, std::string b) {
    while (true) {
        size_t t = s.find(a);
        if (t == std::string::npos) {
            break;
        }
        s.replace(t, a.length(), b);
    }
    return s;
}

void dfs(fs::path path, int depth, std::ofstream &f) {
    for (fs::directory_entry i : fs::directory_iterator(path)) {
        std::string filename =
            replace(replace(i.path().filename().string(), " ", "_"), "\\", "/");
        std::string path =
            replace(replace(i.path().string(), " ", "%20"), "\\", "/");
        if (i.is_directory() && i.path().filename() != ".git") {
            for (int j = 0; j < depth; j++) {
                f << "  ";
            }
            f << "- " << filename << '\n';
            dfs(i.path(), depth + 1, f);
        }
        if (i.is_regular_file() && i.path().extension() == ".md") {
            for (int j = 0; j < depth; j++) {
                f << "  ";
            }
            f << "- [" << filename << "](" << path << ")\n";
        }
    }
}

std::vector<std::string> read() {
    std::ifstream f("README.md", std::istream::binary);
    std::vector<std::string> content;
    std::string tmp;
    while (true) {
        int c = f.get();
        if (c == -1) {
            if (!tmp.empty()) {
                content.emplace_back(std::move(tmp));
            }
            break;
        } else if (c == '\r' || c == '\n') {
            if (c == '\r') {
                f.get();
            }
            content.emplace_back(std::move(tmp));
        } else {
            tmp.push_back(c);
        }
    }
    f.close();
    for (auto i : content) {
        std::cout << i << std::endl;
    }
    return content;
}

std::string lstrip(const std::string &s) {
    int i = 0;
    while (i < s.length() && s[i] == ' ') {
        i++;
    }
    return s.substr(i, std::string::npos);
}

int main() {
    auto content = read();
    int state = 0;
    std::ofstream f("README.md", std::ostream::binary);
    for (auto i : content) {
        if (state == 0) {
            if (i == "<!-- tree2md -->") {
                state = 1;
            }
        } else if (state == 1) {
            if (i == "") {
                state = 2;
            } else {
                state = -1;
            }
        } else if (state == 2) {
            if (!lstrip(i).starts_with("- ")) {
                state = -1;
            }
        }

        if (state != 2) {
            f << i << '\n';
        }
        if (state == 1) {
            f << '\n';
            dfs(".", 0, f);
        }
    }
    if (state == 0) {
        f << "<!-- tree2md -->\n";
        f << '\n';
        dfs(".", 0, f);
    }
    f.close();
    return 0;
}