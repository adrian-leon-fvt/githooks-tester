# githooks-tester

Demonstrator for shared, version-controlled git hooks. Hooks catch style,
sanitization, and breakage issues locally, before code reaches GitHub.

## Setup

One command per clone (git ≥ 2.9):

```sh
git config core.hooksPath .githooks
```

Git now runs hooks from `.githooks/` instead of `.git/hooks/`. Hooks live in
the repo, so everyone gets same checks and updates via normal `git pull`.

Requirements: `bash`, `clang-format`, `make`, `g++`. Optional: `shellcheck`
(shell scripts are skipped if missing).

On Windows, run from Git Bash or WSL. If hooks don't fire, check they are
executable: `git update-index --chmod=+x .githooks/*`.

## Hooks

| Hook         | When                 | Checks                                                                                                                                       |
| ------------ | -------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| `pre-commit` | `git commit`         | trailing whitespace, conflict markers, files > 1 MiB, `clang-format` on staged C/C++, `shellcheck` on scripts, obvious secrets (AWS/GitHub tokens, private keys, `password = "..."`) |
| `commit-msg` | after message typed  | [Conventional Commits](https://www.conventionalcommits.org): `type(scope)?: subject`, ≤ 72 chars                                             |
| `pre-push`   | `git push`           | blocks direct push to `main`, blocks `fixup!`/`squash!`/`WIP` commits, runs `make test`                                                      |

`pre-commit` checks the **staged** content, not the working tree, so partially
staged files are judged on what will actually be committed.

## Try it

```sh
# Style failure
printf 'int  main(){return 0;}\n' > src/bad.cpp && git add src/bad.cpp
git commit -m "feat: bad"          # blocked: not clang-formatted
clang-format -i src/bad.cpp && git add src/bad.cpp

# Message failure
git commit -m "added stuff"        # blocked: not conventional
git commit -m "feat: add bad.cpp"  # ok

# Secret failure
echo 'api_key = "abcdef123456"' > cfg.txt && git add cfg.txt
git commit -m "chore: cfg"         # blocked: possible secret

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
.githooks/     pre-commit, commit-msg, pre-push
.clang-format  team C++ style (Microsoft base, 80 cols)
src/           sample code
test/unit/     sample test run by `make test`
```
