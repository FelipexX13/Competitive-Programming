#!/usr/bin/env bash
# Trae los cambios nuevos de leetcode/ y Training_Camp_2026/ desde
# https://github.com/JuanJoseLozano3/Competitive-Programming-Hub.git
set -e

git fetch hub main

for pair in "leetcode:hub-leetcode-split" "Training_Camp_2026:hub-training-split"; do
	prefix="${pair%%:*}"
	branch="${pair##*:}"
	git subtree split --prefix="$prefix" hub/main -b "$branch"
	git subtree merge --prefix="$prefix" "$branch" -m "Sync $prefix from Competitive-Programming-Hub"
	git branch -D "$branch"
done
