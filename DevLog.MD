# DSA Lab Development Log (CS6173)

---

## [2026-08-28] - Day 0: Environment Setup
**Tasks Completed:**
* Initialized the repository for the Advanced Data Structures Laboratory.
* Set up the C++ environment and build tools. 

**Challenges Faced:**
* Configured the Intel compiler toolchain. Discovered during installation that the Intel compiler requires the full Visual Studio IDE to function correctly, rather than just the VS Code editor.

**Next Steps:**
* Map out the directory structure for reusable code and lab assignments.

---

## [2026-08-29] - Day 1: Header Setup & File Structure
**Tasks Completed:**
* Created the `include/` directory to hold reusable C++ headers (`generation`, `numerical`, `sorting`).
* Established the hierarchical folder structure for `Assignments/` to keep driver code separate from library code.
* Wrote initial boilerplate for the random data generators.

**Next Steps:**
* Begin implementing the first assignment algorithms.

---

## [2026-08-31] - Day 2: Assignment 1 (C++)
**Tasks Completed:**
* Implemented simulation of tossing for one and two coins.
* Compared two versions of bubble sort and performed a comparison count based analysis.
* Quick sort and insertion sort comparison based study to find the threshold point where insertion sort performs better than quick sort.
* Designed a hybrid sort where we do use insertion sort for smaller size subproblems.


**Next Steps:**
* Move on to Assignment 2 problem statements.

---

## [2026-09-01] - Day 3: Assignment 2 (C++)
**Tasks Completed:**
* Implemented Monte Carlo estimation for computing $\pi$.
* Completed numerical integration estimation and Miller-Rabin primality testing algorithms.
* Began writing the Randomized QuickSort logic and integrated the testing drivers via CMake.

**Next Steps:**
* Start porting the C++ logic over to Java.

---

## [2026-09-02] - Day 4: Java Port for Assignment 1
**Tasks Completed:**
* Initialized the `java/` directory in the repository.
* Ported Strassen's matrix multiplication algorithm from C++ to Java.
* Figured out the `javac` and `java -cp` terminal commands to compile and run the Java driver without using an external build system.

**Next Steps:**
* Port Assignment 2 to Java and optimize the file structure.

---

## [2026-09-04] - Day 5: Java for Assignment 2 & Repo Maintenance
**Tasks Completed:**
* Simplified the Java directory into a flat package structure (`generation/`, `sorting/`, `numerical/`) for cleaner imports and compilation.
* Drafted the `DataGenerator` class in Java to generate sorted, reversed, and highly inversional arrays.
* Created the official `README.md` and this `DEVLOG.md` for professional project tracking.

**Next Steps:**
* Complete the empirical time-complexity comparisons between deterministic and randomized QuickSort in Java.