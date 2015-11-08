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
- When the tool was added as an option to Valgrind (?)
- Description of the tool: it’s purpose, what it does, how it works (kinda), etc.
	Callgrind is a profiling tool that records the call history among functions in a program's run as a call-graph. By default, the collected data consists of the number of instructions executed, their relationship to source lines, the caller/callee relationship between functions, and the numbers of such calls. Optionally, cache simulation and/or branch prediction (similar to cachegrind) can produce further information about the runtime behavior of an application.

	The profile data is written out to a file at program termination. For presentation of the data, and interactive control of the profiling, two command line tools are provided:
		callgrind_annotate
			this command reads in the profile data, and prints a sorted lists of functions, optionally with source annotation. For graphical visualization of the data, try kcachegrind, which is a KDE/Qt based GUI that makes it easy to navigate the large amount of data that callgrind produces
		callgrind_control
			This command enables you to interactively observe and control the status of a program currently running under callgrind's control, without stopping the program. You can get statistics information as well as the current stack trace, and you can request zeroing of counters or dumping of profile data.
	Callgrind extends the cachegrind functionality by propagating costs across function call boundaries. If function foo calls bar, the costs from bar are added into foo's costs. When applied to the program as a whole, this builds up a picture of so called inclusive costs, that is, where the cost of each function includes the costs of all functions it called, directly or indirectly.

- Options that can be run with each tool
	Should compile with **-g** flag for debugging purposes
	valgrind --tool=callgrind [callgrind options] your-program [program options]
	This prints the backtrace: callgrind_control -b
	This prints the backtrace with event counts: callgrind_control -e -b
	After terminiation, a profile datafile will be generated callgrind.out.<pid>

	To generate a function by function summary from the profile data file, use: callgrind_annotate [options] callgrind.out.<pid>

	
	These options influence the name and format of the profile data files.
	--callgrind-out-file=<file>
	Write the profile data to file rather than to the default output file, callgrind.out.<pid>. The %p and %q format specifiers can be used to embed the process ID and/or the contents of an environment variable in the name, as is the case for the core option --log-file. When multiple dumps are made, the file name is modified further; see below.

	--dump-line=<no|yes> [default: yes]
	This specifies that event counting should be performed at source line granularity. This allows source annotation for sources which are compiled with debug information (-g).

	--dump-instr=<no|yes> [default: no]
	This specifies that event counting should be performed at per-instruction granularity. This allows for assembly code annotation. Currently the results can only be displayed by KCachegrind.

	--compress-strings=<no|yes> [default: yes]
	This option influences the output format of the profile data. It specifies whether strings (file and function names) should be identified by numbers. This shrinks the file, but makes it more difficult for humans to read (which is not recommended in any case).

	--compress-pos=<no|yes> [default: yes]
	This option influences the output format of the profile data. It specifies whether numerical positions are always specified as absolute values or are allowed to be relative to previous numbers. This shrinks the file size.

	--combine-dumps=<no|yes> [default: no]
	When enabled, when multiple profile data parts are to be generated these parts are appended to the same output file. Not recommended.

	6.3.2. Activity options
	These options specify when actions relating to event counts are to be executed. For interactive control use callgrind_control.

	--dump-every-bb=<count> [default: 0, never]
	Dump profile data every count basic blocks. Whether a dump is needed is only checked when Valgrind's internal scheduler is run. Therefore, the minimum setting useful is about 100000. The count is a 64-bit value to make long dump periods possible.

	--dump-before=<function>
	Dump when entering function.

	--zero-before=<function>
	Zero all costs when entering function.

	--dump-after=<function>
	Dump when leaving function.

	6.3.3. Data collection options
	These options specify when events are to be aggregated into event counts. Also see Limiting range of event collection.

	--instr-atstart=<yes|no> [default: yes]
	Specify if you want Callgrind to start simulation and profiling from the beginning of the program. When set to no, Callgrind will not be able to collect any information, including calls, but it will have at most a slowdown of around 4, which is the minimum Valgrind overhead. Instrumentation can be interactively enabled via callgrind_control -i on.

	Note that the resulting call graph will most probably not contain main, but will contain all the functions executed after instrumentation was enabled. Instrumentation can also programatically enabled/disabled. See the Callgrind include file callgrind.h for the macro you have to use in your source code.

	For cache simulation, results will be less accurate when switching on instrumentation later in the program run, as the simulator starts with an empty cache at that moment. Switch on event collection later to cope with this error.

	--collect-atstart=<yes|no> [default: yes]
	Specify whether event collection is enabled at beginning of the profile run.

	To only look at parts of your program, you have two possibilities:

	Zero event counters before entering the program part you want to profile, and dump the event counters to a file after leaving that program part.

	Switch on/off collection state as needed to only see event counters happening while inside of the program part you want to profile.

	The second option can be used if the program part you want to profile is called many times. Option 1, i.e. creating a lot of dumps is not practical here.

	Collection state can be toggled at entry and exit of a given function with the option --toggle-collect. If you use this option, collection state should be disabled at the beginning. Note that the specification of --toggle-collect implicitly sets --collect-state=no.

	Collection state can be toggled also by inserting the client request CALLGRIND_TOGGLE_COLLECT ; at the needed code positions.

	--toggle-collect=<function>
	Toggle collection on entry/exit of function.

	--collect-jumps=<no|yes> [default: no]
	This specifies whether information for (conditional) jumps should be collected. As above, callgrind_annotate currently is not able to show you the data. You have to use KCachegrind to get jump arrows in the annotated code.

	--collect-systime=<no|yes> [default: no]
	This specifies whether information for system call times should be collected.

	--collect-bus=<no|yes> [default: no]
	This specifies whether the number of global bus events executed should be collected. The event type "Ge" is used for these events.

	6.3.4. Cost entity separation options
	These options specify how event counts should be attributed to execution contexts. For example, they specify whether the recursion level or the call chain leading to a function should be taken into account, and whether the thread ID should be considered. Also see Avoiding cycles.

	--separate-threads=<no|yes> [default: no]
	This option specifies whether profile data should be generated separately for every thread. If yes, the file names get "-threadID" appended.

	--separate-callers=<callers> [default: 0]
	Separate contexts by at most <callers> functions in the call chain. See Avoiding cycles.

	--separate-callers<number>=<function>
	Separate number callers for function. See Avoiding cycles.

	--separate-recs=<level> [default: 2]
	Separate function recursions by at most level levels. See Avoiding cycles.

	--separate-recs<number>=<function>
	Separate number recursions for function. See Avoiding cycles.

	--skip-plt=<no|yes> [default: yes]
	Ignore calls to/from PLT sections.

	--skip-direct-rec=<no|yes> [default: yes]
	Ignore direct recursions.

	--fn-skip=<function>
	Ignore calls to/from a given function. E.g. if you have a call chain A > B > C, and you specify function B to be ignored, you will only see A > C.

	This is very convenient to skip functions handling callback behaviour. For example, with the signal/slot mechanism in the Qt graphics library, you only want to see the function emitting a signal to call the slots connected to that signal. First, determine the real call chain to see the functions needed to be skipped, then use this option.

	6.3.5. Simulation options
	--cache-sim=<yes|no> [default: no]
	Specify if you want to do full cache simulation. By default, only instruction read accesses will be counted ("Ir"). With cache simulation, further event counters are enabled: Cache misses on instruction reads ("I1mr"/"ILmr"), data read accesses ("Dr") and related cache misses ("D1mr"/"DLmr"), data write accesses ("Dw") and related cache misses ("D1mw"/"DLmw"). For more information, see Cachegrind: a cache and branch-prediction profiler.

	--branch-sim=<yes|no> [default: no]
	Specify if you want to do branch prediction simulation. Further event counters are enabled: Number of executed conditional branches and related predictor misses ("Bc"/"Bcm"), executed indirect jumps and related misses of the jump address predictor ("Bi"/"Bim").

	6.3.6. Cache simulation options
	--simulate-wb=<yes|no> [default: no]
	Specify whether write-back behavior should be simulated, allowing to distinguish LL caches misses with and without write backs. The cache model of Cachegrind/Callgrind does not specify write-through vs. write-back behavior, and this also is not relevant for the number of generated miss counts. However, with explicit write-back simulation it can be decided whether a miss triggers not only the loading of a new cache line, but also if a write back of a dirty cache line had to take place before. The new dirty miss events are ILdmr, DLdmr, and DLdmw, for misses because of instruction read, data read, and data write, respectively. As they produce two memory transactions, they should account for a doubled time estimation in relation to a normal miss.

	--simulate-hwpref=<yes|no> [default: no]
	Specify whether simulation of a hardware prefetcher should be added which is able to detect stream access in the second level cache by comparing accesses to separate to each page. As the simulation can not decide about any timing issues of prefetching, it is assumed that any hardware prefetch triggered succeeds before a real access is done. Thus, this gives a best-case scenario by covering all possible stream accesses.

	--cacheuse=<yes|no> [default: no]
	Specify whether cache line use should be collected. For every cache line, from loading to it being evicted, the number of accesses as well as the number of actually used bytes is determined. This behavior is related to the code which triggered loading of the cache line. In contrast to miss counters, which shows the position where the symptoms of bad cache behavior (i.e. latencies) happens, the use counters try to pinpoint at the reason (i.e. the code with the bad access behavior). The new counters are defined in a way such that worse behavior results in higher cost. AcCost1 and AcCost2 are counters showing bad temporal locality for L1 and LL caches, respectively. This is done by summing up reciprocal values of the numbers of accesses of each cache line, multiplied by 1000 (as only integer costs are allowed). E.g. for a given source line with 5 read accesses, a value of 5000 AcCost means that for every access, a new cache line was loaded and directly evicted afterwards without further accesses. Similarly, SpLoss1/2 shows bad spatial locality for L1 and LL caches, respectively. It gives the spatial loss count of bytes which were loaded into cache but never accessed. It pinpoints at code accessing data in a way such that cache space is wasted. This hints at bad layout of data structures in memory. Assuming a cache line size of 64 bytes and 100 L1 misses for a given source line, the loading of 6400 bytes into L1 was triggered. If SpLoss1 shows a value of 3200 for this line, this means that half of the loaded data was never used, or using a better data layout, only half of the cache space would have been needed. Please note that for cache line use counters, it currently is not possible to provide meaningful inclusive costs. Therefore, inclusive cost of these counters should be ignored.

	--I1=<size>,<associativity>,<line size>
	Specify the size, associativity and line size of the level 1 instruction cache.

	--D1=<size>,<associativity>,<line size>
	Specify the size, associativity and line size of the level 1 data cache.

	--LL=<size>,<associativity>,<line size>
	Specify the size, associativity and line size of the last-level cache.


- Known issues for specific tools

- Example code + output (?)


##Conclusion??
Valgrind is much more than a leak checking tool. Change your perspective: Valgrind is an undefined behavior killer.

Valgrind should be your tool of *first* resort. It not only tells you where your bugs are happening, but why, and it'll tell you this even if your program doesn't crash (unlike GDB on both counts). For what it's worth, GDB is still a very useful tool for getting full stack traces on failed assertions and for debugging concurrent code, among other things.

You may also find it useful to always compile with -pedantic -Wall -Wextra. Your compiler is often smart enough to flag undefined behavior as well. What the compiler misses, Valgrind should catch.

pulled from **http://maintainablecode.logdown.com/posts/245425-valgrind-is-not-a-leak-checker**

All information pulled from the valgrind manuals: http://valgrind.org/docs/manual/cl-manual.html