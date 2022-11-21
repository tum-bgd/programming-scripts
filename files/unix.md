# Unix, Linux, and POSIX

The Linux family of operating systems has been improving in importance in the last decades. The project started as an illustrative implementation of a simple UNIX kernel on top of the 80386 computer and is now the leading operating system in terms of global impact. 

In order to understand Linux, one has to look back into the history as well. Linux is modeled after Unix which is a family of operating systems developed for mainframes. Such computers have been very expensive and available long before the personal computer was available, but a single UNIX mainframe was used by many members of a company.

Hence, topics like user management, access control and parallel execution of different things (for different users) have been at the heart of Unix development, while the simplicity (despite all risks) of the DOS immediate mode was not accessible.

At this point, before looking into the guiding principles of Unix and Linux, we can mention a name here: the basic Unix was mainly developed by Ken Thompson and Dennis Ritchie who has also had huge impact on the development and success of the C programming language. In fact, Unix has been implemented mainly in assembler (a rather raw machine language with almost no abstractions), but later translated in large parts into the C language. And this is one of the earliest predecessors of the programming language we will focus on.

Furthermore, a few principles have been fixed in the early days and have proven successful enough not to be changed that much in the years to come. This group of decisions is referred to as the Unix philosophy, which we will revisit when talking about software and programming.

A famous formulation of the Unix philosophy is due to Douglas McIllroy:

> - Write programs such that they do only one thing and they do it well
> - Write programs such that they can work together
> - Write programs such that they work on textual streams as this is the universal interface

This is often oversimplified to
> Do only a single thing at a time and do it well

Or (more or less the same) as the KISS principle: 

>Keep it simple stupid.

There is a lot to these aspects and we will learn a lot about it. More down to the point, Mike Gancarz gives the following list

- Small is beautiful.
- Make each program do one thing well.
- Build a prototype as soon as possible.
- Choose portability over efficiency.
- Store data in flat text files.
- Use software leverage to your advantage.
- Use shell scripts to increase leverage and portability.
- Avoid captive user interfaces.
- Make every program a filter.

This will guide our gentle introduction to Linux in the sequel.

## POSIX
Unix has led to a joint understanding of how computers should work and it has been very successful. But it has also quickly become an area of debate (see Unix Wars). In order to unify and converge the market, a new standard has been carefully designed and developed (ISO/IEC/IEEE 9945) under the name POSIX.

This standar describes clearly and independent from a concrete implementation defintions of terms, the system interface (concretely in C language including header files), and the command line interpreter and a list of tools.

When learning C (or any other modern language), one will often touch exactly this standard even in a non-Unixoid environment (like Windows).

We will now skip over the definitions and the header files, as they naturally appear when learning programming, but jump right ahead to the list of mandatory utilities that you can expect any unix-like operating system to provide:

For a complete list, please refer to https://pubs.opengroup.org/onlinepubs/9699919799/idx/utilities.html

For our first interaction with these systems, we selected

- ar (nowadays often tar for tape archiver)
- at
- awk
- basename
- bc
- cat
- cd
- chgrp
- chmod
- chown
- compress (nowadays, bz2 and gzip)
- cp
- cut
- date
- dd
- df
- diff
- dirname
- du
- echo
- ed
- env
- ex
- expand
- expr
- false
- fg
- file
- find
- fold
- getopts
- grep
- head
- iconv
- id
- jobs
- join
- kill
- ln
- ls
- man
- mkdir
- mkfifo
- more
- mv
- nl
- paste
- patch
- printf
- ps
- pwd
- read
- rm
- rmdir
- sed
- sh (nowadays often bash)
- sleep
- sort
- split
- tail
- tee
- test
- time
- touch
- tr
- true
- ulimit
- umask
- uname
- uniq
- unlink
- vi (nowadays vim)
- wait
- wc
- who
- xargs
- zcat (gzcat, bzcat)

```{note}
Install a Linux, preferably Debian (with no tasks selected, video follows), and login to the system with the user account you created during installation. Then, inform yourself about the commands using the `man` command.
```



## Linux as seen by a user
In order to understand Linux, we need to understand the command line version of it. With Linux being a multiuser operating system, our adventure starts with logging in to Linux by giving a username and its associated password. Then, we end up with a command line, most typically running the Bourne Again Shell (bash).

Similar to the DOS command line, the system now waits for your instructions and gives you some state information like the current working directory (PWD on Linux, accessible with the `pwd`comamnd). Again, you can now use the programs given to start working with a Linux computer.

First, we will have to navigate the system and in Linux there is no concept of drive letters. Instead, there is one file system root (/) and from there the journey begins. 

We can move around by using cd, we can as well use the special directories . to refer to the current directory and .. to refer to the parent directory in the relevant contexts.

```{note}
Navigate to the main directory, then from there into the bin directory. This directory traditinoally holds user programs. By using a pipe character, you can make the output of a program becoming the input of another such that 
`ls | less` will let you page through all programs in the installation.

Navigate to /home. Show all directories using ls. This should now have one directory per user. Enter whoami to find out your user name.

Navigate to /etc, where Linux configuration is held. All programs should keep their configuration there as a plain text file. Look at the file /etc/fstab using an editor of your choice (vi, vim, emacs, nano).

Navigate to /proc. This holds kernel information and files to interact with the kernel. Look at /proc/meminfo, /proc/partitions and /proc/meminfo to find some information about your computer.
```

## Example: Processing data in a Linux environment
As long as you stick with the Unix principles, Linux provides sufficient tools for 99% of your everyday tasks as a data scientist. No advanced software or programming is required in this context.


In order to illustrate the line of thinking, let us perform a rather simple task: count the words in the definition (RFC) of the HTTP protocol available from [RFC](https://www.rfc-editor.org/rfc/rfc2616.txt)

```
curl https://www.rfc-editor.org/rfc/rfc2616.txt > 2616.txt
```
will just download the document. To simplify the remainder, we create a local copy, so be sure to be in a reasonable directory (maybe create one) first.

In order to find the most frequent word, our task is now to break it down into individual words. We do this by relying on the `tr` tool. Read the man page, but we just turn every space into a newline:
```
cat rfc2616.txt | tr " " "\n"
```

In this command, the file is first output to stdout, but this standard output is bound to the standard input of the tr command. This takes every space (first argument) and turns it into a newline. The output is ugly and long (would keep scrolling for quite some time), hence, we can rely on head to see part of it

```
martin@martin:~/lecture$ cat rfc2616.txt |tr " " "\n" | head -10






Network
Working
Group

martin@martin:~/lecture$

```
Okay, this looks nice, but empty lines will be dominating (this happens, because there are a lot of spaces in the document for layouting page numbers). Let us get rid of empty lines as follows (this is tricky, we will discuss this in the tutorial)
```
martin@martin:~/lecture$ cat rfc2616.txt |tr " " "\n" | sed '/^[[:space:]]*$/d' | head -10
Network
Working
Group
R.
Fielding
Request
for
Comments:
2616
UC
```

Now, we can start counting the words. The easiest way to do this is to sort the output using `sort` and then use the `uniq -c` command to remove successive equal lines outputting the count of removed lines. Let us again limit the amount of screen usage with head:
```
martin@martin:~/lecture$ cat rfc2616.txt |tr " " "\n" | sed '/^[[:space:]]*$/d' | sort |uniq -c | head -10
      1 "
      1 ""
      1 ""%"
      1 "#"
      1 "%
      3 "("
      2 ")"
      1 ")">
     26 "*"
      3 "*",
```

Here, now the first column shows the number of times a string has been seen and we need to find the largest ones.
We do this by sorting again, but numerically using `sort -g` and reversing the direction. As we might be unsure whether it works, we can again work on reduced outputs by keeping the head in the command.


```
martin@martin:~/lecture$ cat rfc2616.txt |tr " " "\n" | sed '/^[[:space:]]*$/d' | sort |uniq -c | head -10 | sort -rg
     26 "*"
      3 "*",
      3 "("
      2 ")"
      1 ")">
      1 "%
      1 "#"
      1 ""%"
      1 ""
      1 "
```

Now, we are almost there: Let us now really look for the ten most frequent words in RFC 2616:

```
martin@martin:~/lecture$ cat rfc2616.txt |tr " " "\n" | sed '/^[[:space:]]*$/d' | sort |uniq -c | sort -rg | head -10
   3532 the
   1579 a
   1349 to
   1298 of
   1006 is
    829 and
    773 in
    661 that
    653 be
    550 for
martin@martin:~/lecture$
```

When you take your time to learn a few (if not all) of the core utilities ([GNU coreutils](https://www.gnu.org/software/coreutils/manual/html_node/index.html)), you can solve almost all problems based on text files considerably faster than with any other environment.

