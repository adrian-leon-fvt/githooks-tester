# githooks-tester

Demonstrator for shared, version-controlled git hooks. Hooks catch style,
sanitization, and breakage issues locally, before code reaches GitHub.

Sample project: browser tic-tac-toe vs. unbeatable AI, split across three
languages so hooks exercise each toolchain:

```
web/ (TypeScript)  --POST /api/move-->  server/ (Python)  --argv-->  engine/ (C++)
   UI, clicks           {"board":"X...."}   validates, serves UI      minimax, prints JSON
```

```sh
npm ci && pip install -r requirements-dev.txt
make run      # build all, open http://localhost:8000
make test     # GoogleTest (ctest) + unittest + node --test
```

CMake exports `compile_commands.json` on every configure and symlinks it into
repo root for clangd / VS Code IntelliSense.

## Setup

One command per clone (git ≥ 2.9):

```sh
git config core.hooksPath .githooks
```

Git now runs hooks from `.githooks/` instead of `.git/hooks/`. Hooks live in
the repo, so everyone gets same checks and updates via normal `git pull`.

Requirements: `bash`, `clang-format`, `cmake`, `ninja`, `g++`, `node` ≥ 22.18
(runs `.ts` tests natively), `python3`, plus `ruff` (`requirements-dev.txt`)
and `prettier`/`tsc` (`npm ci`). GoogleTest: system package if found, else
CMake downloads it. [`betterleaks`](https://github.com/betterleaks/betterleaks#installation) (required, commit blocked if missing). Optional: `shellcheck` (shell
scripts skipped if missing).

On Windows, run from Git Bash or WSL. If hooks don't fire, check they are
executable: `git update-index --chmod=+x .githooks/*`.

## Hooks

| Hook         | When                | Checks                                                                                                                                                                                                                                                                             |
| ------------ | ------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `pre-commit` | `git commit`        | trailing whitespace, conflict markers, files > 1 MiB, `clang-format` on C/C++, `ruff check` + `ruff format` on Python, `prettier` on TS/JSON/HTML, `tsc` type-check, `shellcheck` on scripts, secrets via `betterleaks` (false positives: add fingerprint to `.betterleaksignore`) |
| `commit-msg` | after message typed | [Conventional Commits](https://www.conventionalcommits.org): `type(scope)?: subject`, ≤ 72 chars                                                                                                                                                                                   |
| `pre-push`   | `git push`          | blocks direct push to `main`, blocks `fixup!`/`squash!`/`WIP` commits, runs `make test` (all 3 languages)                                                                                                                                                                          |

`pre-commit` checks the **staged** content, not the working tree, so partially
staged files are judged on what will actually be committed.

## Try it

```sh
# Style failure (same idea for .py via ruff, .ts via prettier)
printf 'int  main(){return 0;}\n' > engine/bad.cpp && git add engine/bad.cpp
git commit -m "feat: bad"          # blocked: not clang-formatted
clang-format -i engine/bad.cpp && git add engine/bad.cpp

# Message failure
git commit -m "added stuff"        # blocked: not conventional
git commit -m "feat: add bad.cpp"  # ok

# Secret failure
echo "github_token = \"ghp_$(head -c 64 /dev/urandom | base64 | tr -dc A-Za-z0-9 | head -c 36)\"" > cfg.txt
git add cfg.txt && git commit -m "chore: cfg"  # blocked: betterleaks

# Push failure
git push origin main               # blocked: use a branch + PR
```

## Bypass

Emergency only: `git commit --no-verify` / `git push --no-verify`. Hooks are
local convenience, not enforcement; mirror these checks in CI and branch
protection for anything that must hold.

## Adding a hook

1. Create `.githooks/<hook-name>` (see `git help githooks` for names).
2. `chmod +x` it. Exit non-zero to abort the git operation.
3. Commit it; teammates get it on next pull.

## Layout

```
.githooks/       pre-commit, commit-msg, pre-push
.clang-format    team C++ style (Microsoft base, 80 cols)
CMakeLists.txt   C++ build, GoogleTest, compile_commands.json
engine/          C++ rules + minimax AI, CLI `ttt_engine <board>`
server/app.py    Python stdlib HTTP server, input validation, calls engine
web/             TypeScript UI (src/ -> dist/ via tsc)
test/unit/       GoogleTest suite for engine
test/            Python + TS tests
```
