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

CMD=/usr/local/bin/chdiff

if [ ! -x "$CMD" ]; then
	APPLICATION_PATH=/Applications/Changes.app

	if [ ! -d "$APPLICATION_PATH" ]; then
	  APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"Changes\" as text" | sed 's/:/\//g')
	fi

	CMD="$APPLICATION_PATH/Contents/Resources/chdiff"
fi

if [ ! -x "$CMD" ]; then
	echo "$(basename $0): Could not find chdiff."
	exit 1
fi

"$CMD" "$LOCAL" "$REMOTE"
