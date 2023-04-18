**Project 3: POSIX Thread Programming** 
----------------------

**Team name:** Operating Systems Project Management and Completion <br />
**Name of the VM:** Group 4 VM <br />
**Password:** CS4500Section001!

**Team members names:** <br />
KC Livingston |
Michael Holubec | Tested coded for all three parts, created graphs representing part 3's data, worked on report. <br />

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

For part three it seemed for the most part it seemed that the run time was very inconsistent and fluctuated a lot between different runs. However it seems our program for the most part has lower runtime (in ms) compared to the original program. Based on the graphs for the amount of threads and the one for K its shown that the trendline for our program is typically under the trendline for the original program showing that ours typically runs faster than the original. However, it also seems that the higher the num of threads that our program struggles a bit more. On the other side the higher the K value the more it seems to stay under the original programs trend line.

The work was divided up in a way where one person worked mainly on the functionality and the other worked on testing/data. There was a lot of communication between the group members so that this project was completed and tested ahead of its due date. The only improvement for the project would be for the optimization of part three, but things can almost always be optimized further as we opted to use the optimization we had since it was sufficient enough for the project requirements.

**Lessons Learned:** <br />
----------------------
Michael:
I learned about how important optimization can be and how little things can impact it overall. In most cases it was difficult to tell the average runtime completion, but it was noticible between the original and our program how the average was more consistent with our own. This seems like it can be really important for programs that need to run fast and consistently fast depending on the purpose. However, I also learned optimization is never perfect and sometimes doesn't impact the results much at all at lower values.
