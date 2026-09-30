#!/usr/bin/env bash
# Trae los cambios nuevos de leetcode/ y RPC/ desde
# https://github.com/JuanJoseLozano3/Competitive-Programming-Hub.git
set -e

# Training_Camp_2026/ NO se sincroniza: el Hub tiene el mismo material que
# C++/Training_Camp_2026/, y esa es la copia que se mantiene a mano. Traerlo
# de aca metia cada problema del camp dos veces al notebook.

git fetch hub main

for pair in "leetcode:hub-leetcode-split" "RPC:hub-rpc-split"; do
	prefix="${pair%%:*}"
	branch="${pair##*:}"
	git subtree split --prefix="$prefix" hub/main -b "$branch"
	git subtree merge --prefix="$prefix" "$branch" -m "Sync $prefix from Competitive-Programming-Hub"
	git branch -D "$branch"
done
