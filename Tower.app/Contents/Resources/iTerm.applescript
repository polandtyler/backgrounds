on execute(filename)
    set command_string to "cd " & quoted form of filename

    tell application "iTerm"
        make new terminal

        tell the current terminal
            activate current session
            launch session "Default Session"

            tell the last session
                write text command_string
            end tell
        end tell
    end tell
end execute
