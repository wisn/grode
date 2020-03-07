# Grode

Grode CLI — A CLI-based auto grader that just works.

This repository contains an example for using Grode.
You may see `PS3-LP1920.pdf` which contains the problem description and the testcase.
Then, match every single things there to `inputs/`, `outputs/`, and `scores/`.
Finally, see `submissions/` for all code submissions.

## Prerequisite

A `g++` version `7.4.0` with C++11 standard library.

## Compile

Assume that you are using UNIX-based operating system.
Make sure you have `g++` installed.

```
g++ grode.cpp -std=c++11 -o grode
```

## Run Program

Assume that you are using UNIX-based operating system.
We can now run the program with this command below.

```
./grode
```

You will see something like this on your terminal:

```
grode>
```

Type `help` and then ENTER to see the help message.

## How to Use

Just follow the exact same steps like below.

```
grode> help
  Grode CLI — A CLI-based auto grader that just works
  
  version v0.1.0
  submit an issue to <github.com/wisn/grode>
  
  Command List:
    help                                     display this message
    help <topic>                             display help message for certain topic
    exit                                     close this program
  
    config get <key>                         retrieve current config of certain key
    config set <key> <value>                 set a config for a certain key
  
    fetch input                              retrieve available inputs from input_path
    fetch output                             retrieve available outputs from output_path
    fetch scores                             retrieve available scores from score_path
    fetch submission                         retrieve available submissions from
                                             submission_path
  
    list config                              display all configurations
    list input                               display all loaded inputs
    list output                              display all loaded outputs
    list score                               display all loaded scores
    list submission                          display all loaded submissions
  
    judge <submission_id> all                grade all probems in a certain submission
    judge <submission_id> [<problem_code>]   grade certain problem in a certain submission
grode> list config
  ---------------------------------------------------------------
  | Key                          | Value                        |
  ---------------------------------------------------------------
  | input_path                   | ./inputs                     |
  | output_path                  | ./outputs                    |
  | score_path                   | ./scores                     |
  | submission_path              | ./submissions                |
  ---------------------------------------------------------------
grode> fetch input
  Inputs loaded.
grode> list input
  -----------------------------------
  | Problem Code | Input Files      |
  -----------------------------------
  | 1-a          | 1-a_1.in         |
  |              | 1-a_2.in         |
  |              | 1-a_3.in         |
  |              | 1-a_4.in         |
  |              | 1-a_5.in         |
  -----------------------------------
  | 1-b          | 1-b_1.in         |
  |              | 1-b_2.in         |
  |              | 1-b_3.in         |
  |              | 1-b_4.in         |
  |              | 1-b_5.in         |
  -----------------------------------
  | 2            | 2_1.in           |
  |              | 2_2.in           |
  |              | 2_3.in           |
  |              | 2_4.in           |
  |              | 2_5.in           |
  |              | 2_6.in           |
  |              | 2_7.in           |
  -----------------------------------
  | 3            | 3_1.in           |
  |              | 3_2.in           |
  |              | 3_3.in           |
  |              | 3_4.in           |
  |              | 3_5.in           |
  -----------------------------------
  | 4-1          | 4-1_1.in         |
  |              | 4-1_2.in         |
  -----------------------------------
  | 4-2          | 4-2_1.in         |
  |              | 4-2_2.in         |
  -----------------------------------
  | 5            | 5_1.in           |
  |              | 5_2.in           |
  |              | 5_3.in           |
  |              | 5_4.in           |
  |              | 5_5.in           |
  |              | 5_6.in           |
  |              | 5_7.in           |
  |              | 5_8.in           |
  |              | 5_9.in           |
  |              | 5_10.in          |
  -----------------------------------
grode> fetch output
  Outputs loaded.
grode> list output
  -----------------------------------
  | Problem Code | Output Files     |
  -----------------------------------
  | 1-a          | 1-a_1.out        |
  |              | 1-a_2.out        |
  |              | 1-a_3.out        |
  |              | 1-a_4.out        |
  |              | 1-a_5.out        |
  -----------------------------------
  | 1-b          | 1-b_1.out        |
  |              | 1-b_2.out        |
  |              | 1-b_3.out        |
  |              | 1-b_4.out        |
  |              | 1-b_5.out        |
  -----------------------------------
  | 2            | 2_1.out          |
  |              | 2_2.out          |
  |              | 2_3.out          |
  |              | 2_4.out          |
  |              | 2_5.out          |
  |              | 2_6.out          |
  |              | 2_7.out          |
  -----------------------------------
  | 3            | 3_1.out          |
  |              | 3_2.out          |
  |              | 3_3.out          |
  |              | 3_4.out          |
  |              | 3_5.out          |
  -----------------------------------
  | 4-1          | 4-1_1.out        |
  |              | 4-1_2.out        |
  -----------------------------------
  | 4-2          | 4-2_1.out        |
  |              | 4-2_2.out        |
  -----------------------------------
  | 5            | 5_1.out          |
  |              | 5_2.out          |
  |              | 5_3.out          |
  |              | 5_4.out          |
  |              | 5_5.out          |
  |              | 5_6.out          |
  |              | 5_7.out          |
  |              | 5_8.out          |
  |              | 5_9.out          |
  |              | 5_10.out         |
  -----------------------------------
grode> fetch score
  Scores loaded.
grode> list score
  ----------------------------
  | Problem Code | Max Score |
  ----------------------------
  | 1-a          | 10        |
  | 1-b          | 10        |
  | 2            | 20        |
  | 3            | 20        |
  | 4-1          | 10        |
  | 4-2          | 10        |
  | 5            | 20        |
  ----------------------------
grode> fetch submission
  Submissions loaded.
grode> list submission
  --------------------------------------------------------------------------------------------------
  | ID  | Submission Name          | 1-a     | 1-b     | 2     | 3     | 4-1     | 4-2     | 5     |
  --------------------------------------------------------------------------------------------------
  | 1   | PS3-ehardi.pl            | 0.00    | 0.00    | 0.00  | 0.00  | 0.00    | 0.00    | 0.00  |
  | 2   | PS3-ganeshadanu.pl       | 0.00    | 0.00    | 0.00  | 0.00  | 0.00    | 0.00    | 0.00  |
  --------------------------------------------------------------------------------------------------
grode> judge 2 all
  Judging "PS3-ganeshadanu.pl"
    Taking problem "1-a".
      Result for "1-a_1": AC
      Result for "1-a_2": AC
      Result for "1-a_3": AC
      Result for "1-a_4": AC
      Result for "1-a_5": AC
    Scored 10.00 out of 10
    Taking problem "1-b".
      Result for "1-b_1": AC
      Result for "1-b_2": AC
      Result for "1-b_3": AC
      Result for "1-b_4": AC
      Result for "1-b_5": AC
    Scored 10.00 out of 10
    Taking problem "2".
      Result for "2_1": AC
      Result for "2_2": AC
      Result for "2_3": TLE
      Result for "2_4": TLE
      Result for "2_5": AC
      Result for "2_6": AC
      Result for "2_7": AC
    Scored 14.29 out of 20
    Taking problem "3".
      Result for "3_1": AC
      Result for "3_2": AC
      Result for "3_3": AC
      Result for "3_4": AC
      Result for "3_5": AC
    Scored 20.00 out of 20
    Taking problem "4-1".
      Result for "4-1_1": AC
      Result for "4-1_2": AC
    Scored 10.00 out of 10
    Taking problem "4-2".
      Result for "4-2_1": AC
      Result for "4-2_2": AC
    Scored 10.00 out of 10
    Taking problem "5".
      Result for "5_1": AC
      Result for "5_2": AC
      Result for "5_3": AC
      Result for "5_4": AC
      Result for "5_5": AC
      Result for "5_6": AC
      Result for "5_7": AC
      Result for "5_8": AC
      Result for "5_9": AC
      Result for "5_10": AC
    Scored 20.00 out of 20
grode> list submission
  --------------------------------------------------------------------------------------------------
  | ID  | Submission Name          | 1-a     | 1-b     | 2     | 3     | 4-1     | 4-2     | 5     |
  --------------------------------------------------------------------------------------------------
  | 1   | PS3-ehardi.pl            | 0.00    | 0.00    | 0.00  | 0.00  | 0.00    | 0.00    | 0.00  |
  | 2   | PS3-ganeshadanu.pl       | 10.00   | 10.00   | 14.29 | 20.00 | 10.00   | 10.00   | 20.00 |
  --------------------------------------------------------------------------------------------------
grode> exit
```

## TODO

- [ ] Refactor the whole code and make it more modular.
- [ ] Implement dynamic table formatting.
- [ ] Implement "fetch all" command.
- [ ] Prevent fetch submission before score.
- [ ] Add support for multiple programming languages.

## License

Licensed under [The MIT License](LICENSE).
