# Algorithm — competitive programming practice

This repository is a personal workspace for practicing competitive programming and algorithm problems (C++, Java, Python, etc.). It is organized by topic and contest source so you can quickly find and solve problems, track progress, and reuse templates.

## Layout / important folders

- `AlgoMonster/` — topic-based folders and practice checklists (Arrays, Graphs, DP ...)
- `CSES/` — solutions and notes for CSES problems
- `Leetcode/`, `Codeforces/`, `AtCoder/` — platform-specific directories
- `DynamicPrograming/`, `Graph/`, `SortingAndSearching/` — categorized collections

Tip: Use the folder names to mirror problems or topics you want to focus on.

## How I use this repo (recommended)

- Keep one solution per file using a clear name, e.g. `two_sum.cpp`, `dijkstra.cpp`.
- Add a short comment at the top with the problem name, source, difficulty, and tags.
- Add a `README.md` or `problems.md` in a topic folder to track which problems are done and notes.

## Compile & run (common commands)

For C++ (single file):

```bash
g++ -std=c++17 -O2 -pipe path/to/file.cpp -o file && ./file
```

Run with input from file:

```bash
./file < input.txt
```

For quick testing, use `run.sh` or a makefile if you prefer. If you want, I can add templates for each language.

## Naming conventions

- Source files: `problem_name.cpp` (snake_case) or `topic_problem.cpp`.
- Tests / inputs: `problem_name.in` / `problem_name.out`.
- Use a header comment with: problem link, tags, time complexity.

## Progress tracking & workflow

- Keep a simple checklist in topic `README.md` files or in the root `progress.md`.
- Use branches for bigger refactors, but for single-problem solutions working on `main` is fine.
- Commit frequently with messages like `solve: <problem-name> (platform, difficulty)`.

## Contribution / personal guidelines

- Add solutions with clear filenames and minimal dependencies.
- Prefer self-contained files so they compile without extra project setup.
- When adding multiple files for the same problem, put them in a subfolder with a `README.md`.

## Practice tips

- Focus on one topic for a week (e.g., graphs or DP) and solve 10–20 problems from easy→hard.
- Write brief editorial notes after solving: approach, pitfalls, and alternative solutions.
- Time yourself when practicing contest simulations.

## Want templates or automation?
I can add:
- language templates (C++ fast I/O + template),
- a small `run.sh` to compile & run a file, or
- `README.md` templates inside topic folders to track progress.

If you'd like any of those, tell me which language(s) and I will add them.

---

Last updated: October 2025
