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

APPLICATION_PATH=/Applications/TextMate.app

if [ ! -d "$APPLICATION_PATH" ]; then
  APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"TextMate\" as text" | sed 's/:/\//g')
fi

CMD="$APPLICATION_PATH/Contents/SharedSupport/Support/bin/mate"

diff -u "$LOCAL" "$REMOTE" | "$CMD" -a
