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

APPLICATION_PATH="/Applications/Araxis Merge.app"

if [ ! -d "$APPLICATION_PATH" ]; then
	APPLICATION_PATH=/Volumes/$(osascript -e "path to application \"Araxis Merge\" as text" | sed 's/:/\//g')
fi

DIFF_CMD="$APPLICATION_PATH/Contents/Utilities/araxisgitdiff"
MERGE_CMD="$APPLICATION_PATH/Contents/Utilities/araxisgitmerge"

if [ ! -x "$DIFF_CMD" ]; then	
	DIFF_CMD=`which araxisgitdiff`	
fi

if [ ! -x "$DIFF_CMD" ]; then
	DIFF_CMD=/usr/local/bin/araxisgitdiff
fi

if [ ! -x "$DIFF_CMD" ]; then
	DIFF_CMD=/usr/bin/araxisgitdiff
fi

if [ ! -x "$DIFF_CMD" ]; then
	DIFF_CMD=$HOME/bin/araxisgitdiff
fi

if [ ! -x "$MERGE_CMD" ]; then
	MERGE_CMD=`which araxisgitmerge`
fi

if [ ! -x "$MERGE_CMD" ]; then
	MERGE_CMD=/usr/local/bin/araxisgitmerge
fi

if [ ! -x "$MERGE_CMD" ]; then
	MERGE_CMD=/usr/bin/araxisgitmerge
fi

if [ ! -x "$MERGE_CMD" ]; then
	MERGE_CMD=$HOME/bin/araxisgitmerge
fi

if [ -n "$MERGING" ]; then
	if [ ! -x "$MERGE_CMD" ]; then
		echo "Could not find Araxis Merge's araxisgitmerge executable. Please make sure you have installed the command line utils from the Araxis disk image installer." >&2
		exit 128
	fi
	
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

  "$MERGE_CMD" "$LOCAL" "$BASE" "$REMOTE" "$MERGE" # araxisgitmerge script expects this order of parameters
else
	if [ ! -x "$DIFF_CMD" ]; then
		echo "Could not find Araxis Merge's araxisgitdiff executable. Please make sure you have installed the command line utils from the Araxis disk image installer." >&2
		exit 128
	fi
	
  "$DIFF_CMD" /dev/null "$LOCAL" /dev/null /dev/null "$REMOTE" # araxisgitdiff expects old style git diff params at $2 and $5...
fi

if [ -n "$MERGING" ]; then
	# Check if the merged file has changed
	if [ "$MERGE" -ot "$BACKUP" ]; then
		exit 1
	fi	
fi

exit 0
