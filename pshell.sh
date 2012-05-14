#!/bin/bash
# Hourse of pshell.cpp

. /etc/pvm.conf

args=(${@})
cmd=${args[0]}
unset args[0]

cmdfile="/tmp/pshell-cmd-$RANDOM"

case "$cmd" in
"/PDNSoftCo./Scripts/pvmctl")
	echo $sudo $pvmctl ${args[@]} > $cmdfile
	;;
"/PDNSoftCo./Scripts/pcad")
	echo $sudo $pcad ${args[@]} > $cmdfile
	;;
"pvmctl")
	echo $sudo $pvmctl ${args[@]} > $cmdfile
	;;
"pcad")
	echo $sudo $pcad ${args[@]} > $cmdfile
	;;
"pinfox")
	echo $sudo $pinfox ${args[@]} > $cmdfile
	;;
"echo")
	if [[ "${args[1]}" = "y" ]]; then
		echo "echo y" > $cmdfile
	else if [[ "${args[1]}" = "-e" && "${args[2]}" = "\"y\ny\n\"" ]]; then
		echo 'echo -e "y\ny\n"' > $cmdfile
	fi
	fi
	;;
"scp")
	if [[ "${args[1]}" = "-t" || "${args[1]}" = "-p" ]]; then
		# retreive path
		if [[ ${args[2]} = "--" || "${args[2]}" = "-t" ]]; then
			dst_path="${args[3]}"
		else
			dst_path="${args[2]}"
		fi

		# restrict scp location to vm storages
		tx=$( read_config_file "$cf_VMStorages"| while read __i; do
			__path=$(echo $__i | $cut -s -d ";" -f 3)
			if [[ $(expr $dst_path : "\"$__path") -ne "0" ]]; then
				echo "accept"
				exit 0
			fi
			if [[ $(expr $dst_path : "$__path") -ne "0" ]]; then
				echo "accept"
				exit 0
			fi
		done )

		if [[ -z "$tx" ]]; then 
			if [[ $(expr $dst_path : "/pvm/VMStorage") -eq 0 && \
						$(expr $dst_path : "\"/PDNSoftCo./VMStorage") -eq 0 ]]; then
					echo_error "Bad scp command ..."
					exit 1
			fi
		fi
		echo $sudo scp -q ${args[@]} > $cmdfile
	else if [[ "${args[1]}" = "-f" ]]; then
		# download action ...
		dst_path="${args[2]}"
		# restrict scp location to vm storages
		tx=$( read_config_file "$cf_VMStorages"| while read __i; do
			__path=$(echo $__i | $cut -s -d ";" -f 3)
			if [[ $(expr $dst_path : "\"$__path") -ne "0" ]]; then
				echo "accept"
				exit 0
			fi
			if [[ $(expr $dst_path : "$__path") -ne "0" ]]; then
				echo "accept"
				exit 0
			fi
		done )

		if [[ -z "$tx" ]]; then 
			if [[ $(expr $dst_path : "/pvm/VMStorage") -eq 0 && \
						$(expr $dst_path : "\"/PDNSoftCo./VMStorage") -eq 0 ]]; then
					echo_error "Bad scp command ..."
					exit 1
			fi
		fi
		echo $sudo scp -q ${args[@]} > $cmdfile
	else
		echo_error "Bad scp command ..."
		exit 1
	fi
	fi
	;;
"PIPED")
	cmd=${args[1]}
	unset args[1]
	case $cmd in
	"grep")
		echo $grep ${args[@]} > $cmdfile
		;;
	"awk")
		echo $awk ${args[@]} > $cmdfile
		;;
	"sed")
		echo $sed ${args[@]} > $cmdfile
		;;
	"/PDNSoftCo./Scripts/pvmctl")
		echo $sudo $pvmctl ${args[@]} > $cmdfile
		;;
	"/PDNSoftCo./Scripts/pcad")
		echo $sudo $pcad ${args[@]} > $cmdfile
		;;
	*)
		echo_error "Bad piped command ..."
		exit 1
		;;
	esac
	;;
"help")
	echo "You can run this commands: pvmctl, pcad, pinfox."
	echo "Use help of them for more information (e.g. pvmctl help)"
	exit 0
	;;
*)
	echo_error "Bad Command ..."
	exit 1
	;;
esac

# running command
. $cmdfile
rm $cmdfile 2>/dev/null

