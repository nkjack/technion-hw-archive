#!/bin/tclsh

proc comp_file {file1 file2} {
    # optimization: check file size first
    set equal 0
    if {[file size $file1] == [file size $file2]} {
        set fh1 [open $file1 r]
        set fh2 [open $file2 r]
        set equal [string equal [read $fh1] [read $fh2]]
        close $fh1
        close $fh2
    }
    return $equal
}
set test_files [glob tests/prev/*.in]
set num_tests [llength $test_files]
exec make
source add_main_to_tests.tcl
set crashed_tests ""
foreach file $test_files {
	set res_file [lindex [split $file .] 0].res
	set out_file [lindex [split $file .] 0].out
	set asm_file [lindex [split $file .] 0].asm
	catch {exec ./hw5 < $file > $asm_file} err
	if {$err ne ""} {
		# we have a problem! not good at all!
		lappend crashed_tests $file
		continue
	}
	catch {exec ./spim -file $asm_file > $res_file} err
	if {$err ne ""} {
		lappend crashed_tests $file
		continue
	}
	if {[comp_file $out_file $res_file]} {
		incr num_tests -1
		file delete $asm_file
		file delete $res_file
	}
}
if {$num_tests == 0} {
	puts "############################################################"
	puts "################### ALL CLEAN ##############################"
	puts "############################################################"
} else {
	puts "############################################################"
	puts "################### Failed #################################"
	puts "############################################################"
	set res_files [glob tests/prev/*.res]
	puts "To check results run the following commands"
	foreach file $res_files {
		puts "diff [lindex [split $file .] 0].out $file"
	}
	puts "The following tests have crashed... This is very sad..."
	foreach file $crashed_tests {
		puts tests/prev/$file	
	}
}
