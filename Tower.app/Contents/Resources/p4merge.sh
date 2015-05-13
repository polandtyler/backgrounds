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

MERGING="$4"
BACKUP="/tmp/$(date +"%Y%d%m%H%M%S")"

APPLICATION_PATH=/Applications/p4merge.app

if [ ! -d "$APPLICATION_PATH" ]; then
  APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"P4Merge\" as text" | sed 's/:/\//g')
fi

CMD="$APPLICATION_PATH/Contents/MacOS/p4merge"

if [ ! -x "$CMD" ]; then
	echo "P4Merge application could not be found!" >&2
	exit 128
fi

if [ -n "$MERGING" ]; then
	BASE="$3"
	MERGE="$4"
	
	# Sanitize BASE path
	if [[ ! "$BASE" =~ ^/ ]]; then
		BASE=$(echo "$BASE" | sed -e 's/^\.\///')
		BASE="$PWD/$BASE"
		
		if [ ! -f "$BASE" ]; then
			BASE=/dev/null
		fi
	fi
	
	# Sanitize MERGE path
	if [[ ! "$MERGE" =~ ^/ ]]; then
		MERGE=$(echo "$MERGE" | sed -e 's/^\.\///')
		MERGE="$PWD/$MERGE"

		if [ ! -f "$MERGE" ]; then
			# For conflict "Both Added", Git does not pass the merge param correctly in current versions
			MERGE=$(echo "$LOCAL" | sed -e 's/\.LOCAL\.[0-9]*//')
		fi
	fi
	
	sleep 1 # required to create different modification timestamp
	touch "$BACKUP"

	"$CMD" "$BASE" "$LOCAL" "$REMOTE" "$MERGE" # P4Merge expects this order of arguments
else
  "$CMD" "$LOCAL" "$REMOTE"
fi

if [ -n "$MERGING" ]; then
	# Check if the merged file has changed
	if [ "$MERGE" -ot "$BACKUP" ]; then
		exit 1
	fi	
fi

exit 0
