#!/usr/bin/python3
import re
from typing import Sequence, Tuple, Callable, Collection
from enum import Enum, auto
from itertools import groupby

# TODO: enforce these
Keybinding = str
Description = str
Line = Sequence[str]
Hotkey = Tuple[Keybinding, Description]
Config = Sequence[Hotkey]

class Command(Enum):
    Key = auto()
    Mouse = auto()

    def __repr__(self) -> str:
        return f"{self.name}Cmd"

def tokenize(line: str) -> Line:
    def remove_all(s: str, olds: str) -> str:
        if olds == "":
            return s
        else: 
            return remove_all(s.replace(olds[0], ''), olds[1:])

    return list(map(str.strip, remove_all(line.strip(), "{}").split(',')))

def categorize(keybinding: Line) -> Tuple[Command, Line]:
    if "MODKEY" in keybinding[0]:
        return (Command.Key, keybinding)
    else:
        return (Command.Mouse, keybinding)

def shorten(cmd: Tuple[Command, Line]) -> Tuple[Command, Line]:
    if cmd[0] is Command.Key:
        return (cmd[0], cmd[1][0].split('|') + [cmd[1][1]] + [cmd[1][4]])
    else:
        return (cmd[0], [cmd[1][0], cmd[1][1], cmd[1][2], cmd[1][5]])

def format(cmd: Tuple[Command, Sequence[str]]) -> Hotkey:
    def cmd_format(args: Sequence[str], extra: str = "") -> Hotkey:
        not_empty: Callable[[str], bool] = lambda x: x != ""
        return [
            "+".join(list(filter(not_empty, args))) + extra, 
            cmd[1][-1][3:].capitalize()
        ]

    def beautify_k(hotkey: Line) -> Hotkey:
        return cmd_format([
            f"{hotkey[0].title()[:3]}", 
            f"{hotkey[1][:-4]}" if len(hotkey) == 4 else "", 
            f"{hotkey[1 if len(hotkey) == 3 else 2][3:].title()}"
        ])

    def beautify_m(hotkey: Line) -> Hotkey:
        def fix(x: str) -> str:
            return (x if x == '1' else ('2' if x == '3' else '3'))

        def unabbreviate(abr: str) -> str:
            if abr == "LtSymbol":   return "Layout Symbol"
            if abr == "WinTitle":   return "Window Title"
            if abr == "StatusText": return "Clock"
            if abr == "ClientWin":  return "Window"
            if abr == "TagBar":     return "Workspace"

        return cmd_format([
                f"{hotkey[1].title()[:3]}" if hotkey[1] != '0' else "",
                f"Mouse{fix(hotkey[2][-1])}"
            ],
            f" on {unabbreviate(hotkey[0][3:])}"
        )

    if cmd[0] is Command.Key:
        return beautify_k(cmd[1])
    else:
        return beautify_m(cmd[1])

def parse(config: str) -> Config:
    def convert(x: str) -> Hotkey:
        return format(shorten(categorize(tokenize(x))))

    k = re.compile(r"^\s\{ .*[})] },.*$", re.MULTILINE)
    with open(config, "r") as f:
        z = re.findall(k, "".join(f.readlines()))

    return list(map(convert, z))

def show_keybindings() -> None:
    def bifurcate(l: Config) -> Config:
        z: Config = [(x[0], x[1]) for x in l]
        y: Config = list(filter(lambda x: "Mouse" not in x[0], z))
        return [y, list(set(z) - set(y))]

    def maxlen(group: Sequence[Hotkey]) -> int:
        return len(max(group, key=lambda x: len(x[0]))[0])

    for group in bifurcate(parse("/opt/dwm-distrotube-git/config.h")):
        for key in group:
            print(f"{key[0].ljust(maxlen(group))}: {key[1]}")
        print()

def main() -> None:
    show_keybindings()

main()
