#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::u8string replace(std::u8string s, std::u8string a, std::u8string b) {
    while (true) {
        size_t t = s.find(a);
        if (t == std::string::npos) {
            break;
        }
        s.replace(t, a.length(), b);
    }
    return s;
}

std::string dfs(fs::path path, int depth) {
    std::string result;
    auto it = fs::directory_iterator(path);
    std::vector<fs::directory_entry> entries(fs::begin(it), fs::end(it));
    std::sort(entries.begin(), entries.end(),
              [](const fs::directory_entry &a, const fs::directory_entry &b) {
                  auto sa = a.path().filename().u8string();
                  auto sb = b.path().filename().u8string();
                  for (size_t i = 0; i <= std::min(sa.length(), sb.length());
                       i++) {
                      auto ca = tolower(sa[i]);
                      auto cb = tolower(sb[i]);
                      if (ca != cb) {
                          return ca < cb;
                      }
                  }
                  return sa > sb;
              });
    for (const fs::directory_entry &i : entries) {
        std::u8string filename =
            replace(i.path().filename().u8string(), u8"\\", u8"/");
        std::u8string path = replace(
            replace(i.path().u8string(), u8" ", u8"%20"), u8"\\", u8"/");
        if (i.is_directory() && i.path().filename().u8string()[0] != '.') {
            std::string next = dfs(i.path(), depth + 1);
            if (next != "") {
                for (int j = 0; j < depth; j++) {
                    result += "  ";
                }
                result += (std::string) "- " + (char *)filename.data() + '\n';
                result += next;
            }
        }
        if (i.is_regular_file() && i.path().extension() == ".md") {
            for (int j = 0; j < depth; j++) {
                result += "  ";
            }
            result += (std::string) "- [" + (char *)filename.data() + "](" +
                      (char *)path.data() + ")\n";
        }
    }
    return result;
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
    return content;
}

std::string lstrip(const std::string &s) {
    int i = 0;
    while (i < (int)s.length() && s[i] == ' ') {
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
            f << dfs(".", 0);
        }
    }
    if (state == 0) {
        f << "<!-- tree2md -->\n";
        f << '\n';
        f << dfs(".", 0);
    }
    f.close();
    return 0;
}
