The Disk Operating System (DOS)
=======

In order to fully understand Microsoft Windows and in order to get to
advanced usage capabilities, it is unavoidable to understand, how
Microsoft Windows has emerged. In the old days of computing, a company
named Microsoft introduced an operating system known as Disk Operating
System (DOS) which was used to run most personal computers in these
days. From a user perspective, this operating system did all the work of
starting up the computer and configuring hardware and running programs.
Therefore, a command line was designed and equipped with programs and
technology to support basic computing tasks.

MS Dos was a single tasking operating system (except TSRs, which have
been small programs that were able to run in the background). This
dictates the logic under which interaction with MS Dos is cut into
sequential steps. In a nutshell, the computer tells the user that it
waits for an instruction by showing a command prompt.

```
C:\>
```

The user is then supposed to enter a command which then runs a program
or a builtin instruction. Only four types of information are available
to both the user and programs:

- The current working directory (CWD) which is a combination of a
    drive and a folder relative to which all file operations are
    performed

- A set of environment variables, such as the %PATH% variable

- The name of the program and a space-separated list of arguments to
    the command

In this context, the DOS provided a set of commands for working with
these states and software vendors could provide additional programs.
While DOS can be considered history, all current Windows versions
include a Command Prompt feature, which provides a DOS-like command line
to perform tasks on Windows computers. For an overview, we list a few
DOS commands and ask you to explore them yourself on a Windows computer
(or in FreeDOS in a virtual machine like Virtual Box).

Each command starts with the name of the command or program and a set of
arguments where arguments starting with a "/" are considered switches
that just influence the behavior. Many file-oriented commands allow you
to use wildcards. A wildcard in a string matches zero or more character
(\*) or exactly one unspecified character (?). For more clarity:

- stat\*.bat would match status.bat as well as stat.bat

- data?.dat would match data0.dat, but not data10.dat

Basic programs

- \<drive letter\>: to change the drive

- CD to change the directory

- DIR to list a directory, consider switches /P and /S which change
    the behavior

- MD to create a directory

- RD to remove a directory (only if empty)

- TREE shows all files below the current working directory

- ATTRIB show and modify attributes like write protection on files

- COPY is used to copy files

- DEL deletes files (synonymous with ERASE)

- EDIT provides a simple editor (EDLIN before MS DOS 6.0)

- FIND searches for a string in a file

- MORE pages a file to the screen

- MOVE moves a file to a different location

- PRINT is used to print a file

- REPLACE works like copy but replaces the file in the target

- TYPE outputs the whole content of the given file

- XCOPY extends COPY to be able to copy whole directories and trees

- CLS clears the screen

- DATE shows and modifies the date

- TIME shows and modifies the time

- ECHO is used to control whether commands are shown or not (mainly in
    batch files)

- FDISK is used to set up hard disks (partitions, etc.)

- FORMAT organizes a file system on floppy disks or hard disk
    partitions

- HELP shows help for a dos command (use it in the tutorial!)

- SET shows configuration information and environment variables and
    modifies them

- VER shows the version of DOS in use

With these commands, it is possible to organize a computer quite nicely
yet remaining simple and self-explaining. Another interesting aspect
about DOS which is visible in modern versions of Windows is the fact
that file names were heavily restricted in early versions allowing 8
characters for the file name and 3 characters for the file name
extension separated with a dot. Extensions have always been used to mark
the type of file, for example article.txt was a text file suitable for
the edit program while word.exe was a program known as Word which could
be run by writing the command word (without the extension) when in the
same directory or when the directory was mentioned in the PATH variable.

```{note}
**Assignment 1:**

-   Install VirtualBox and run FreeDOS inside

-   Using the FreeDOS command line, create a folder structure
    representing Germanys federal structure. Start by creating a folder
    Germany, within this folder, create one for each state.

-   In each state, create a file capital.txt and write into it only the
    name of the capital of the state in one line (be sure to end the
    line)

-   Show the tree (and submit as a solution) using the command line

-   (Advanced) Output all member states

-   Learn about the redirection of output using the \> pipe

-   Look around on your Windows PC if you have one. Where is your data
    stored technically, where is Documents located? Where are Downloads?
    Try to find out about this by just running the "Command Prompt" or
    "Eingabeaufforderung" in German language.

-   Create a file on the Desktop of your Windows Computer, use the
    extension .txt and write Hello Windows into it. Then open the file
    with the Windows GUI which should spill up your favourite editor.
```

DOS used drive letters A, B, C, etc. to distinguish different disks. In
the very early days, one typically had no hard drive in an MS DOS
computer, but one floppy disk. This disk was known as A and all the life
was taking place in A:\>. A bit later, many computers came up with a
second floppy drive. Now, the drive A was used to start the operating
system (DOS) and provide commands, while B:\> was used to store data. As
floppy disks are sometimes usable (when a valid disk has been inserted)
and sometimes unusable, both letters are reserved up to today.
Typically, the first drive letter assigned to hard drives or other
modern devices is, therefore, C:\>. In almost all versions of Windows
today, Windows is installed on a drive with letter C. If the main drive
has more partitions, drive letters are used sequentially, such that a
two-partition setup often has a drive D:\>. On many other computers, D:
already refers to some CD drive or USB stick. In a nutshell, drive
letters are assigned along the alphabet and as the first two letters are
reserved for floppy drives, the first letter in every-day use is C. As a
consequence of this unknown dynamics, it has become a tradition to map
the first network drive with the letter Z and to continue backwards (if
you are in a network-enabled environment). Furthermore, some companies
have started to use a drive called H like "Home" for the home drive of a
user.

```{note}
**Assignment Two: Install Windows (at least once)**

Windows Installation Tutorial. When you start working with Windows a
lot, you will face the situation that your computer is not working
properly anymore. In this tutorial (accessible only for people with a
valid Windows license), we will install Windows into a virtual machine
to train the procedure. In order to help you for your future, we ask you
to do this on a virtual disk of 20 GB (use a FCOW disk to save space)
which you partition into three disks: Disk C (the main Windows disk)
shall use 10 GB, while a drive D of 5 GB and a drive E of 5 GB shall be
available as well. Therefore, you can use the partitioning tool part of
the Windows installer. We will use Windows Education 11, but the
procedure is not much different for any (unmodified) Windows.
```

Automation in Windows
=====================

Since the beginning (including MS DOS), the builtin functionality can be
used to automate routine tasks to some extent. In Windows, batch files
are being used. In their simplest form, batch files just list a sequence
of commands to be executed one after another. But batch files can have
more aspects such as looping over files, asking for user input and other
advanced patterns. As many of our students will be exposed to a Windows
with no access to advanced scripting software, it is worth knowing some
basic aspects of how to write batch files on Windows.

As said, a batch file is just a text file in ASCII format and each row
of the file represents a command which you could as well type into the
command prompt. However, it gets more interesting if one realizes the
following three functionalities:

- Disabling the output

- Looping over files

- Using arguments given to the batch file

The first aspect is simple, but important: in basic batch files, each
command is first output before the command is executed and the output of
the execution is output. This means that it is a bit tricky to have
concise output from a batch script which is really useful for the user.
In a batch file, the output of a command can be suppressed by prefixing
it with @ why it is good practice to start all batch files with a line

```
\@echo off
```

The output of this line is suppressed (it would typically output "ECHO
is disabled") and the output of commands is disabled for the remainder
of the script.

Now, it is very common that batch files are used to automate annoying
commands to avoid typing and thereby avoiding typos as well. Imagine you
are working on satellite images and you have downloaded 1,000 scenes
from Sentinel 2. As you want to create a web map, you decided to
reproject all of these files from their own projection into a
WebMercator projection (EPSG 90009001). You figured out the right
parameters for letting gdal\_warp utility doing your work, for example

```
gdal\_warp \<scene\> -t\_srs ... (please figure it out yourself!)
```

Then, you can use a batch file like this one:

```
\@echo off
for %%f in (\*.tif) do (
gdal\_warp \<magic parameters here\> %%\~nf output/%%\~nf
)
```

This file takes all files with extension tif in the current directory
and gives them as input to our magic gdal\_warp command while putting
the result into the same file, but in a directory output. Hence, be sure
to have this directory created (or make the creation of this directory
part of the batch script itself). In this way, you can now have a lot of
coffee or go to bed while your computer is working through your archive
of data.

```{note}
**Assignment Three: Writing Batch Files**

Create a batch file which reproduces the result of Assigment One. A
batch file in Microsoft DOS and Windows is a simple ASCII text file with
an extension of .BAT. Those files can be run from the command prompt
just like EXE files by giving their name without extension. Use the
\@ECHO OFF as the first line to suppress the output of the individual
programs. Explore on your own using the Internet, how one can get input
from the user into a variable, how one can loop over files running a
certain command for each file.
```

```{note}
**Assignment Four: Learn some Latin**

We will write a batch file program to train latin vocabulary. Therefore,
we create a file with the latin name containing the translation
(followed by a newline). Then, try to write a script that first selects
a file at random (or any other way) and asks (by showing the filename
representing the latin vocabulary). Then ask the user to input and
(!maybe!) try to compare the user input with the file contents at least
roughly. Note that this can be really tricky in BATCH programming, so
any approximate solution is appreciated.

*Just some tips: To make it less complex, the solution to this task was
not comparing the results, but rather showing the user input and the
translation from the file. Further, we create two Batch files: one which
loops over all files and another one which is called with the filename
and presents a short dialog. *
```

```{note}

**Assignment Five: Reproject Sentinel Scenes**

Download a handful of Sentinel scenes from different locations, install
GDAL and use the gdal\_warp command line utility to bring all the files
into the same projection.
```
