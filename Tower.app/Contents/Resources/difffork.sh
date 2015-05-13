#!/bin/sh

LOCAL="$1"
REMOTE="$2"

# Sanitize LOCAL path
if [[ ! "$LOCAL" =~ ^/ ]]; then
	LOCAL=$(echo "$LOCAL" | sed -e 's/^\.\///')
	LOCAL="$PWD/$LOCAL"
fi

# Sanitize REMOTE path
if [[ ! "$REMOTE" =~ ^/ ]]; then
	REMOTE=$(echo "$REMOTE" | sed -e 's/^\.\///')
	REMOTE="$PWD/$REMOTE"
fi

APPLICATION_PATH=/Applications/DiffFork.app

if [ ! -d "$APPLICATION_PATH" ]; then
	APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"DiffFork\" as text" | sed 's/:/\//g')
fi

DIFFFORK="$APPLICATION_PATH/Contents/SharedSupport/Support/bin/difffork"

if [ ! -x "$DIFFFORK" ]; then
	echo "DiffFork application could not be found!" >&2
	exit 128
fi

"$DIFFFORK" "$LOCAL" "$REMOTE" -w

exit 0
