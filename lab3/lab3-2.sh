#!/bin/bash
function urldecode() { : "${*//+/ }"; echo -e "${_//%/\\x}"; }
echo "Content-type: text/html"
echo ""
echo '<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"><meta charset="UTF-8"><title>lab3-2</title></head><body>'
if [ "$REQUEST_METHOD" = "POST" ]; then
        if [ "$CONTENT_LENGTH" -gt 0 ]; then
		POST_STRING="$(cat)"
                QUERY_STRING=(${POST_STRING//&/ })
		QUERY_TYPE_BLOCK=${QUERY_STRING[2]}
                QUERY_TYPE=(${QUERY_TYPE_BLOCK//=/ })
                QUERY_TYPE=${QUERY_TYPE[1]}

		FILENAME_BLOCK=${QUERY_STRING[0]}
                FILENAME=(${FILENAME_BLOCK//=/ })
                FILENAME=${FILENAME[1]}

		TEXT_BLOCK=${QUERY_STRING[1]}
                TEXT=(${TEXT_BLOCK//=/ })
                TEXT=${TEXT[1]}

 		if [ "$QUERY_TYPE" = "Download" ]; then
                	FILE_CONTENT=$(cat "$FILENAME" 2>&1)
        	fi

		if [ "$QUERY_TYPE" = "Save" ]; then
                        ERROR=$(cp "$FILENAME" "./copy/$FILENAME" 2>&1)

			DECODED=$(urldecode "$TEXT")
                        ERROR_WRITE=$(echo "$DECODED" > "./$FILENAME" 2>&1)
		fi
	fi
fi
echo $ERROR
echo "<form method=\"post\" action=\"lab3-2.sh\"><input placeholder=\"Path to file\" name=\"filename\" value=\"$FILENAME\"/><br><br><textarea name=\"text\" rows=\"10\" cols=\"70\">"
echo "$FILE_CONTENT"
echo '</textarea><br><input type="submit" name="file" value="Download"><br><br><input type="submit" name="file" value="Save"/></form>'
echo '</body></html>'
exit 0
