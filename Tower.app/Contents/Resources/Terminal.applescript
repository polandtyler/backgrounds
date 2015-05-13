on execute(filename)
    tell application "System Events" to set terminal_active to (exists process "Terminal")

    if (terminal_active) then
        tell application "Terminal"
            do script "cd " & quoted form of filename
            activate
        end tell
    else
        tell application "Terminal"
            do script "cd " & quoted form of filename in the front window
            activate
        end tell
    end if
end execute
