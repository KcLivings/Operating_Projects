**Project 3: POSIX Thread Programming** 
----------------------

**Team name:** Operating Systems Project Management and Completion <br />
**Name of the VM:** Group 4 VM <br />
**Password:** CS4500Section001!

**Team members names:** <br />
KC Livingston | Wrote code for all three tasks, assisted report, created framework for project by creating initial files
 <br />
 Michael Holubec | Tested coded for all three parts, created graphs representing part 3's data, worked on report.

**Description of Project:**  <br />
------------------------
The main purpose of this project is to learn how to use Pthread properly in programs. Additionally, we are to learn how to use mutexes/condition variables and learn how to design efficient code using these programming practices and be and able to compare and contrast that to an existing programs efficient.

**Pseudocode:**  <br />
----------------------
This can be a picture, drawing, sketch, or digitally produced. For example, if you
hand-wrote it on a sheet of paper, convert it into and image and paste it here. If you typed it
in notepad, copy and paste it here. <br />
A rough draft of how you plan to design your program should be included here. You can
do this in pseudocode or flowchart format. The idea is to begin thinking about how you will
formulate your program and how you will ensure you obtain the results the assignment is
describing.

**Conclusion:**  <br />
--------------------

For part two it behaved how we expected it to for the most part. The producer read from the file and put it into the queue and then the consumer read the queue and printed in the right order. This was tested with multiple lines to see if continued working which it did. However, one issue we ran into was that once the file was fully read it did not terminate/stop. There was no real issues in part one as it behaved as how we expected it to.

For part three, To help improve the performance of the program, I figured there was a few things I could do: Use a fine-grained locking strategy, use a lock-free data structure, use thread-local lists, use thread pooling, and optimize memory allocation. In the end, and to simplify the program, and due to the given restraints, I modified the code to use thread-local lists, cleaned it up with a simpler structure, and optimized the memory management to better optimize the way the threads are utilized and lessen the time it took to create and manage the list that the code is building. </br>
The run times for both programs was very inconsistent and fluctuated a lot between different runs. However, it our program, for the most part, had lower runtimes (in ms) compared to the original program. Based on the graphs, one for the amount of threads and one for different K values, it's shown that the trendline for our program is typically under the trendline for the original program, showing that ours typically runs faster than the original. However, it also seems that with higher numbers of threads, our program struggles a bit more. On the other side, the higher the K value the better it performs against the original program.

The work was divided up in a way where one person worked mainly on the functionality and the other worked on testing/data. There was a lot of communication between the group members so that this project was completed and tested ahead of its due date. The only improvement for the project would be for the optimization of part three, but things can almost always be optimized further as we opted to use the optimization we had since it was sufficient enough for the project requirements.

**Lessons Learned:** <br />
----------------------
Michael:
I learned about how important optimization can be and how little things can impact it overall. In most cases it was difficult to tell the average runtime completion, but it was noticible between the original and our program how the average was more consistent with our own. This seems like it can be really important for programs that need to run fast and consistently fast depending on the purpose. However, I also learned optimization is never perfect and sometimes doesn't impact the results much at all at lower values.

Kc: 
Pthread creation was not something I had ever worked with before so it posed an initial issue in figuring out how to work with it. After a few trial an error test runs, I was able to get a basic enough grasp that I felt comfortable to begin working on the tasks. Task 2 was relatively easy due to a similar experience I am having with another class, but task 3 posed some problems for me. Optimization is another thing that I have little experience with. Overall, however, there were no absolutely major challenges that we encountered that couldn't be resolved with a little effort.
