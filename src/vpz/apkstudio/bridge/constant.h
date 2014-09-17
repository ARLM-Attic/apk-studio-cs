#ifndef VPZ_APKSTUDIO_BRIDGE_CONSTANT_H
#define VPZ_APKSTUDIO_BRIDGE_CONSTANT_H

#define APPLICATION_DOMAIN "www.vaibhavpandey.com"
#define APPLICATION_NAME "APK Studio"
#define APPLICATION_ORGANIZATION "VPZ"

#define EDITOR_BACKGROUND "#FFFFFF"
#define EDITOR_FOREGROUND "#333333"
#define EDITOR_HIGHLIGHT "#DCF5FF"
#define EDITOR_LINE "#999999"
#define EDITOR_SELECTION "#666666"
#define EDITOR_SIDEBAR "#DEDEDE"
#define EDITOR_TRIGGER 2

#define FORMAT_TIMESTAMP "yyyy-MM-dd hh:mm:ss"

#define PATH_COMPLETION ":/res/completion/"
#define PATH_FONT ":/res/font/"
#define PATH_HIGHLIGHT ":/res/highlight/"
#define PATH_ICON ":/res/icon/"
#define PATH_IMAGE ":/res/image/"
#define PATH_LANGUAGE ":/res/language/"

#define PREFERENCE_BINARIES "binaries"
#define PREFERENCE_HEAP "heap"
#define PREFERENCE_HEAP_DEFAULT 128
#define PREFERENCE_ROOT "root"
#define PREFERENCE_TEXT "text"
#define PREFERENCE_VERBOSE "verbose"

#define REGEX_ACCESS "(?<path>.*)\\.(accdb|accde|accdr|accdt)"
#define REGEX_ADOBE "(?<path>.*)\\.pdf"
#define REGEX_APPLICATION "^package:(?<path>.+?)=(?<package>.+)$"
#define REGEX_APK "(?<path>.*)\\.apk"
#define REGEX_AUDIO "(?<path>.*)\\.(?<extension>amr|mp3|wav)"
#define REGEX_EMULATOR "emulator-(?<port>\\d+)"
#define REGEX_EPUB "(?<path>.*)\\.epub"
#define REGEX_EXCEL "(?<path>.*)\\.(ods|xla|xll|xlm|xls|xlw|xlsb|xlsm|xltm|dot|dotm|dotx)"
#define REGEX_FILENAME "^[A-Za-z0-9\\-\\._\\s]+$"
#define REGEX_FLASH "(?<path>.*)\\.flv"
#define REGEX_GETPROP "^\\[(?<key>[^]]+)\\]\\:\\s*\\[(?<value>.*)\\]$"
#define REGEX_IMAGE "(?<path>.*)\\.(?<extension>jpg|jpeg|png|tiff)"
#define REGEX_IMEI "\\s=\\s"
#define REGEX_LOGCAT "^(?<time>\\d\\d-\\d\\d\\s\\d\\d:\\d\\d:\\d\\d\\.\\d+)\\s*(?<pid>\\d+)\\s*(?<tid>\\d+)\\s(?<priority>[VDIWEAF])\\s(?<tag>.*?):\\s+(?<message>.*)$"
#define REGEX_LS "^(?<permission>[bcdlsp-][-r][-w][-xsS][-r][-w][-xsS][-r][-w][-xstST])\\s+(?<owner>\\S+)\\s+(?<group>\\S+)\\s+(?<size>[\\d\\s,]*)\\s+(?<date>\\d{4}-\\d\\d-\\d\\d)\\s+(?<time>\\d\\d:\\d\\d)\\s+(?<name>.*)$"
#define REGEX_PHP "(?<path>.*)\\.(phar|php|php3|php4|php5|phtml)"
#define REGEX_PHOTOSHOP "(?<path>.*)\\.(?<extension>psb|psd)"
#define REGEX_PROJECT "^[A-Za-z0-9_]+$"
#define REGEX_POWERPOINT "(?<path>.*)\\.(pot|potm|potx|ppam|pps|ppsm|ppsx|ppt|pptm|pptx|sldm|sldx)"
#define REGEX_STATE "(?<message>.*):\\s+(?<state>disable|enabled)"
#define REGEX_TAG "^[A-Za-z0-9_]+$"
#define REGEX_TRANSFER "(?<speed>\\d+)\\sKB\\/s\\s\\((?<byte>\\d+)\\s.*\\s(?<second>\\d+\\.\\d+)s\\)"
#define REGEX_VIDEO "(?<path>.*)\\.(?<extension>3gp|mp4|mpg|mpeg|webm|wmv)"
#define REGEX_WEBSITE "(?<path>.*)\\.(dhtml|htm|html|shtml|xml)"
#define REGEX_WORD "(?<path>.*)\\.(odt|doc|docm|docx|dot|dotm|dotx|wpd)"

#define ROLE_PATH 997
#define ROLE_STRUCT 998
#define ROLE_TYPE 999

#endif // VPZ_APKSTUDIO_BRIDGE_CONSTANT_H
