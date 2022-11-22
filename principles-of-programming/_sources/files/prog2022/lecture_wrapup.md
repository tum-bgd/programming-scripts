
The idea of Task 5 Tunnel is to write a function that does "one step" and calls
itself to do the next step.

Then, after fulfilling the goal (finding the item) the recursion can unwrap.

That is the function is a primary recursion of the form
```
go one step
check if done
go back one step
```

The step information is known by the execution path.

Primary Recursion - In the past (1928, David Hilbert) one believed that all intuitively computable functions are of this type.
# Learn some command line

- cd : change directory
- md / mkdir: make folder
- rm / rmdir
- delete
- touch
- dir / ls on Linux/MAc
- Learn Filename Patterns  `*.txt*`*
- grep: Filter the output of the previous program to only show lines matching a pattern
	- grep -v DEBUG
- cut: get certain bytes or fields by number (like second column...)

# Algorithms

Not yet valuable examples for remembering, just tools for learning loops.

# Python
- Loops
- List Expressions / Dict Expressions
- Conditions
- Types and Type Conversions 
- Strings, because Strings are bad in Python
	- As strings have very strict rules, expect EncodingErrors to happen.
	- To avoid them, you can use the byte type
	- But the byte type does not provide string functionality
	- Task sheet on Strings is important to experience the problems
Whatevery we learn today and next week.

# Python still missing
- Object Orientation (typically used, but not always of high value)
- Extensions

# Numpy
- Creation of NDarrays
- Working with the shape (getting the shape, changing the shape)
- Combining (np.stack and np.hstack and np.vstack) 
- Slicing
- Showing images

# Check Rasterio 
