from pathlib import Path
from typing import List


def dfs(path: Path, depth: int):
    result = ""
    children = path.iterdir()
    children = sorted(children, key=lambda path: path.name.lower())
    for i in children:
        filename = i.name
        pathname = i.as_posix().replace(" ", "%20")
        if i.is_dir() and not i.name.startswith("."):
            next = dfs(i, depth + 1)
            if next != "":
                result += "  " * depth
                result += f"- {filename}\n"
                result += next
        if i.is_file() and i.suffix == ".md":
            result += "  " * depth
            result += f"- [{filename}]({pathname})\n"
    return result


def main():
    LABEL: str = "<!-- tree2md -->"
    content: List[str] = Path("README.md").read_text().split("\n")
    if LABEL in content:
        index = content.index(LABEL)
        del content[index]
    else:
        index = len(content)
    while index - 1 >= 0 and content[index - 1] == "":
        del content[index - 1]
        index -= 1
    while index < len(content) and content[index] == "":
        del content[index]
    while index < len(content) and content[index].strip().startswith("- "):
        del content[index]
    while index < len(content) and content[index] == "":
        del content[index]
    content.insert(index, "\n" + LABEL + "\n\n" + dfs(Path("."), 0))
    Path("README.md").write_text("\n".join(content))
