proc addMainForProc {file} {
	# File to list
	set fh [open $file "r"]
	set text [read $fh]
	close $fh
	regexp {void[\ \r\n\t]+main} $text res
	if {![info exist res]} {
		set fh [open $file "w+"]
		puts $fh $text
		set func_name [regexp -inline {maxTests[^\n]*} $text]
		set func_name [lindex [split $func_name '\('] 0]
		puts $fh "void main() {"
		puts $fh "     ${func_name}();"
		puts $fh "     print(\"\\nI hate this course\\n\");" 
		puts $fh "}"
		close $fh
		return
	}
	unset res
}
set input_files [glob tests/test*.in]
foreach file $input_files {
	addMainForProc $file
}
