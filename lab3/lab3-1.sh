#!/bin/bash

echo "Content-type: text/html"
echo ""
echo '<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"><meta charset="UTF-8"><title>lab3.1</title></head><body>'
date
echo "<br>"
uptime
echo "<br>"
uname -a
echo "<br>"
id
echo "<br>"
echo $HTTP_X_FORWARDED_FOR
echo "<br>"
echo $HTTP_USER_AGENT
echo "<br>"
echo "<br>"
echo '<form method="post" action="lab3.sh"><input name="name"></label><input type="submit"></input></form>'
if [ "$REQUEST_METHOD" = "POST" ]; then
	if [ "$CONTENT_LENGTH" -gt 0 ]; then
		POST_STRING="$(cat)"
		echo "Input: $POST_STRING <br>"
		COMMAND_ARRAY=(${POST_STRING//=/ })
		COMMAND=${COMMAND_ARRAY[1]}
		COMMAND=${COMMAND//+/ }
		echo "Command: <strong>$COMMAND</strong><br>"
		echo 'Result:<br><code style="font-size: 18px">'
		eval $COMMAND
		echo "</code><br>"
	fi
fi
echo '</body></html>'
exit 0
