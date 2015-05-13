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

CMD=`which ksdiff`

if [ ! $CMD > /dev/null ] ; then
  if [ -e '/usr/local/bin/ksdiff' ] ; then
    CMD='/usr/local/bin/ksdiff'
  fi
fi

if [ ! -x "$CMD" ]; then    
  echo "Kaleidoscope's command line tool 'ksdiff' could not be found. Please make sure it has been installed in /usr/local/bin/." >&2
  exit 128
fi

OLD_CMD_VERSION=$($CMD --supports-capability merges-v1 | grep -c "NO")

if [ -n "$MERGING" ]; then
  if [ "$OLD_CMD_VERSION" -eq 1 ]; then
    echo "Kaleidoscope's command line tool does not support merging." >&2
    exit 128
  fi
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
  
  "$CMD" --merge --base "$BASE" --output "$MERGE" -- "$LOCAL" --snapshot "$REMOTE" --snapshot
else
  if [ "$OLD_CMD_VERSION" -eq 1 ]; then
    "$CMD" --wait "$LOCAL" "$REMOTE"
  else
    MERGE="$3"

    if [ -n "$MERGE" ]; then
        "$CMD" --partial-changeset --relative-path "$MERGE" -- "$LOCAL" "$REMOTE"
    else
        "$CMD" --diff "$LOCAL" "$REMOTE"
    fi
  fi
fi

if [ -n "$MERGING" ]; then
  # Check if the merged file has changed
  if [ "$MERGE" -ot "$BACKUP" ]; then
    exit 1
  fi
fi

exit 0
