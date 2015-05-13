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

CMD=`which bbdiff`

if [ ! -x "$CMD" ]; then
	CMD=/usr/local/bin/bbdiff
fi

if [ ! -x "$CMD" ]; then
	CMD=/usr/bin/bbdiff
fi

if [ ! -x "$CMD" ]; then
	CMD=$HOME/bin/bbdiff
fi

if [ ! -x "$CMD" ]; then	
	APPLICATION_PATH=/Applications/BBEdit.app

	if [ ! -d "$APPLICATION_PATH" ]; then
	  APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"BBEdit\" as text" | sed 's/:/\//g')
	fi
	
	CMD="$APPLICATION_PATH/Contents/Helpers/bbdiff"
fi

if [ ! -x "$CMD" ]; then
	echo "$(basename $0): Could not find bbdiff. If you have purchased BBEdit from the\nMac AppStore you have to download and install the command line tools separately."
	exit 1
fi

"$CMD" --wait --resume "$LOCAL" "$REMOTE"
