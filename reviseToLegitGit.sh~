#!/bin/sh

# ==========
#   Config
# ==========

REPO_TO="[https://github.com/shi428/Hardest-Touhou-Final-Boss.git]"

# Create temporary directory
TMP_DIR=$(mktemp -d -t ci-XXXXXXXXXX);

# Setup a trap to clear tempdir and execute on EXIT
trap "rm -rf $TMP_DIR" EXIT

# Copy over
cp -r * .git .gitignore $TMP_DIR

# Change directory
cd $TMP_DIR

ls $TMP_DIR

# Execute change
git filter-branch --env-filter '

OLD_EMAIL="[41700122+sometard123@users.noreply.github.com]"

CORRECT_NAME="[shi428]"
CORRECT_EMAIL="[shi428@purdue.edu]"

if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" ]
then
  export GIT_COMMITTER_NAME="$CORRECT_NAME"
  export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" ]
then
  export GIT_AUTHOR_NAME="$CORRECT_NAME"
  export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags

# Correct push location
git remote rm origin
git remote add origin $REPO_TO
git push origin master

# Clean up
rm -rf $TMP_DIR
