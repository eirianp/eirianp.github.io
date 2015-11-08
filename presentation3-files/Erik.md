##Background:

*Who developed?* There is a group of developers from all over the world, that work together and have authorization to work on the Valgrind repository core code. Requests can be made to join the development team. The Valgrind Development can be found at **http://valgrind.org/info/developers.html**  A request to become a developer for Valgrind can be done through this site **https://lists.sourceforge.net/lists/listinfo/valgrind-developers**

*Why developed?* Originally, Valgrind was meant to be a memory free debugging tool for linux on x86 systems, but has since evolved into a framework for creating dynamic analysis tools such as checkers and profilers. [wikipedia: https://en.wikipedia.org/wiki/Valgrind]

*Systems it works with?* Valgrind works with Linux, OS X, Solaris and Android. And most recent stable release 3.11 on September 22, 2015.

*Software* It is open source/free software readily available under the GNU General Public License, version 2

*Valgrind Overview*
```
	Valgrind is in essence a virtual machine using just-in-time (JIT) compilation techniques, including dynamic recompilation. Nothing from the original program ever gets run directly on the host processor. Instead, Valgrind first translates the program into a temporary, simpler form called Intermediate Representation (IR), which is a processor-neutral, SSA-based form. After the conversion, a tool (see below) is free to do whatever transformations it would like on the IR, before Valgrind translates the IR back into machine code and lets the host processor run it. Even though it could use dynamic translation (that is, the host and target processors are from different architectures), it doesn't. Valgrind recompiles binary code to run on host and target (or simulated) CPUs of the same architecture. It also includes a GDB stub to allow debugging of the target program as it runs in Valgrind, with "monitor commands" that allow you to query the Valgrind tool for various sorts of information.
	A considerable amount of performance is lost in these transformations (and usually, the code the tool inserts); usually, code run with Valgrind and the "none" tool (which does nothing to the IR) runs at 1/4 to 1/5 of the speed of the normal program
```
^ Thank you wikipedia

*Awards/Motivation* May 2008: Valgrind won TrollTech's inaugural Qt Open Source Development Award for the best open source development tool.
July 2006: Julian Seward won a Google-O'Reilly Open Source Award for "Best Toolmaker" for his work on Valgrind.
Open Source Award	
January 2004: Valgrind won a merit (bronze) Open Source Award.

*Projects using or have used Valgrind* found here: http://valgrind.org/gallery/users.html

*Something to know* Valgrind is not just a leak checker, it can help find latent bugs even when they don't cause your program to fail or crash -> refers to the difficulty of black box testing and concurrency problems.
Adding compiler flags will help with debugging with Valgrind because Valgrind will have more information to tell you. 
-pedantic -Wall -Wextra


##Massif
- When the tool was added as an option to Valgrind (?)
- Description of the tool: it’s purpose, what it does, how it works (kinda), etc.
	Massif is a heap profiler. It performs detailed heap profiling by taking refular snapshots of a program's heap. It produces a graph showing heap usage over time, including information about which parts of the program are responsible for the most memory allocations. The graph is supplemented by a text or HTML file that includes more information for determing where the most memory is being allocated. Massif runs programs about 20x slower than normal
	On modern machines with virtual memory, Massif can speed up the program -- interact better with machine's caches and avoid paging, it will help reduece the chance that it exhausts your machine's swap space. Massif c an identify leaks that aren't actually lost, pointers remain to it, but they are no longer in use. Traditional memcheck's may not find these leaks, but Massif can. 
- Options that can be run with each tool.
	When compiling, must use the **-g** flag. to run, **valgrind --tool=massif**. To see the information gathered by Massif in an easy to read form, use ms_print <filename>
	--time-unit=B option to specity that we want the time unit to instead be the number of bytes allocated/deallocated on the heap and stack(s).
	Maximum number of snapshots is 100, although, can change this using --max-snapshots. --detailed-freq option changes how often a detail snapshot is taken (default is everything 10th.)
- Known issues for specific tools
	Massif's determination of when the peak occured can be wrong, for two reasons, Peak snapshots are only ever taken after a deallocation happens. This avoids lots of unnecessary peak snapshot recordings (imagine what happens if your program allocates a lot of heap blocks in succession, hitting a new peak every time). But it means that if your program never deallocates any blocks, no peak will be recorded. It also means that if your program does deallocate blocks but later allocates to a higher peak without subsequently deallocating, the reported peak will be too low.
	Even with this behavior, recording the peak accureately is slow. So by default Massif records a peak whose size is within 1% of the size of the true peak. This unaacuracy in the peak measurement can be changed with the --peak-inaccuracy option.
	If the program forks, the child will inherit all the profiling data that has been gathered for the parent. If the output file format string does not contain %p, then the outputs from the parent and child will be intermingled in a single output file, which will almost certainly make it unreadable by ms_print

	By default, massif measures only heap memory. If you wish to measure all the memory used by your program, you can use the --pages-as-heap=yes
	command-line options:
		--heap=<yes|no> default: yes
			Specifies whether heap profiling should be done
		--heap-admin=<size> default: 8
			if heap profiling is enabled, gives the number of admin bytes per block to use. This should be an estimate of the average, since it may vary.
		--stacks=<yes|no> default: no
			Specifies whether stack profiling should be done. This option slows Massif down greatly and so is off by default
		--pages-as-heap=<yes|no> defailt: no
			Tells Massif to profile memory at the page level rather than at the malloc's block level
		--depth=<number> default: 30
			Maximum depth of the allocation trees recorded for detailed snapshots. increasing it will make Massif run somewhat more slowly, use more memory, and produce bigger output files
		--alloc-fn=<name>
			functions specified with this option will be treated though they were heap allocation function such as malloc. This is usefull for functions that are wrappers to malloc or new, which can fill up the allocation trees with uninteresting information
			Note: C++ names are demangled. Note also that overloaded C++ names must be written in full. Single quotes may be necessary to prevent the shell from breaking them up
		--ignore-fn=<name>
			Any direct heap allocation  that occurs in a function specified by this option will be ignored. This is mostly useful for resting purposes.
		--threshold=<m.n> default: 1.0
			The significance threshold for heap allocations, as percentage of total memory size
		--peak-inaccuracy=<m.n> default: 1.0
			Massif does not necessarily record the actual global memory allocation peak.
		--time-unit=<i|ms|B> default: i
			The time unit used for the profiling. There are three possibilities: instructions executed (i), real wall clock (ms, milliseconds), and bytes allocated (B)
		--detailed-freq=<n> default: 10
			Frequency of detailed snapshots
		--max-snapshots=<n> default: 100
			The maximum number of snapshots recorded
		--massif-out-file=<file> default: massif.out.%p
			Write the profile data to file rather than to the default output file, massif.out.<pid>

- Example code + output (?)


##Callgrind
- When the tool was added as an option to Valgrind
- Description of the tool: it’s purpose, what it does, how it works (kinda), etc.
- Options that can be run with each tool
- Known issues for specific tools
- Example code + output


##Conclusion??
Valgrind is much more than a leak checking tool. Change your perspective: Valgrind is an undefined behavior killer.

Valgrind should be your tool of *first* resort. It not only tells you where your bugs are happening, but why, and it'll tell you this even if your program doesn't crash (unlike GDB on both counts). For what it's worth, GDB is still a very useful tool for getting full stack traces on failed assertions and for debugging concurrent code, among other things.

You may also find it useful to always compile with -pedantic -Wall -Wextra. Your compiler is often smart enough to flag undefined behavior as well. What the compiler misses, Valgrind should catch.

pulled from **http://maintainablecode.logdown.com/posts/245425-valgrind-is-not-a-leak-checker**