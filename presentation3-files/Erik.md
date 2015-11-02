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
- When the tool was added as an option to Valgrind
- Description of the tool: it’s purpose, what it does, how it works (kinda), etc.
- Options that can be run with each tool
- Known issues for specific tools
- Example code + output


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