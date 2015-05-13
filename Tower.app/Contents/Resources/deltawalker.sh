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

APPLICATION_PATH=/Applications/DeltaWalker.app

if [ ! -d "$APPLICATION_PATH" ]; then
  APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"DeltaWalker\" as text" | sed 's/:/\//g')
fi

if [ ! -d "$APPLICATION_PATH" ]; then
  echo "Could not find DeltaWalker. Please make sure you have installed a recent version of DeltaWalker." >&2
  exit 128
fi

CMD="$APPLICATION_PATH/Contents/MacOS/DeltaWalker"

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

    "$CMD" "$LOCAL" "$REMOTE" "$BASE" -merged="$MERGE" -nosplash -mi -pwd="`pwd`"
else
    "$CMD" "$LOCAL" "$REMOTE" -nosplash -mi -pwd="`pwd`"
fi

if [ -n "$MERGING" ]; then
	# Check if the merged file has changed
	if [ "$MERGE" -ot "$BACKUP" ]; then
		exit 1
	fi	
fi

exit 0
