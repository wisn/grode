#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

void display(vector<string> messages);
vector<string> split(string str, string de);

class File {
  private:
    string path;
    string content;

  public:
    File() {
      this->path = "";
      this->content = "";
    }

    File(string path) {
      this->path = path;
      this->content = "";
    }

    string get_path() {
      return this->path;
    }

    void set_path(string path) {
      this->path = path;
    }

    string get_content() {
      return this->content;
    }

    pair<bool, string> fetch_content() {
      ifstream ifs;
      string buffer = "";
      string content = "";

      ifs.open(this->path, ifstream::in);

      while (ifs.rdstate() == ifstream::goodbit) {
        getline(ifs, buffer);
        content += buffer + "\n";
      }

      if (ifs.rdstate() == ifstream::badbit) {
        return {false, "got a badbit iostate"};
      }

      this->content = content;

      return {true, content};
    }
};

class Directory {
  private:
    string path;
    vector<File> files;

  public:
    Directory() {
      this->path = "";
    }

    Directory(string path) {
      this->path = path;
    }

    string get_path() {
      return this->path;
    }

    void set_path(string path) {
      this->path = path;
    }

    vector<File> list_files() {
      return this->files;
    }

    void get_files() {
      DIR* dir;
      struct dirent* ent;
      function<bool(File, File)> comparator = [](File f, File g) {
        string s = f.get_path();
        string t = g.get_path();

        if (s.size() == t.size()) {
          return s < t;
        }

        return s.size() < t.size();
      };

      if ((dir = opendir(this->path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
          string ent_name = ent->d_name;

          if (ent_name != "." && ent_name != "..") {
            File f (this->path + "/" + ent_name);

            this->files.push_back(f);
          }
        }

        closedir(dir);
      } else {
        display({"Can't retrieve files."});
      }

      sort(this->files.begin(), this->files.end(), comparator);
    }
};

pair<int, string> exec(const char* cmd);

int main(int argc, char* argv[]) {
  string input;

  map<string, string> configurations = {
    {"input_path", "./inputs"},
    {"output_path", "./outputs"},
    {"score_path", "./scores"},
    {"submission_path", "./submissions"},
  };

  map<string, vector<File>> inputs;
  map<string, vector<File>> outputs;
  map<string, int> scores;
  vector<pair<File, map<string, double>>> submissions;

  map<string, function<void(vector<string>)>> supported_commands = {
    {"exit", [](vector<string> arguments) {}},
    {"help", [](vector<string> arguments) {
      if (arguments.size() == 0) {
        display({
          "Grode CLI — A CLI-based auto grader that just works",
          "",
          "version v0.1.0",
          "submit an issue to <github.com/wisn/grode>",
          "",
          "Command List:",
          "  help                                     display this message",
          "  help <topic>                             display help message for certain topic",
          "  exit                                     close this program",
          "",
          "  config get <key>                         retrieve current config of certain key",
          "  config set <key> <value>                 set a config for a certain key",
          "",
          "  fetch input                              retrieve available inputs from input_path",
          "  fetch output                             retrieve available outputs from output_path",
          "  fetch scores                             retrieve available scores from score_path",
          "  fetch submission                         retrieve available submissions from",
          "                                           submission_path",
          "",
          "  list config                              display all configurations",
          "  list input                               display all loaded inputs",
          "  list output                              display all loaded outputs",
          "  list score                               display all loaded scores",
          "  list submission                          display all loaded submissions",
          "",
          "  judge <submission_id> all                grade all probems in a certain submission",
          "  judge <submission_id> [<problem_code>]   grade certain problem in a certain submission",
        });
      } else {
        display({"Not implemented."});
      }
    }},
    {"config", [&configurations](vector<string> arguments) {
      if (arguments.size() == 0) {
        display({"Please specify what to do."});
      } else {
        string operation = arguments[0];

        if (operation == "get") {
          if (arguments.size() > 2) {
            display({
              "Only the first key will be considered.",
              "Executing \"config get " + arguments[1] + "\".",
              "",
            });
          }

          if (arguments.size() == 1) {
            display({"Please specify what to display."});
          } else {
            string key = arguments[1];

            if (configurations.find(key) != configurations.end()) {
              display({key + " => " + configurations[key]});
            } else {
              display({"There is no \"" + key + "\" in the configuration."});
            }
          }
        } else if (operation == "set") {
          if (arguments.size() > 3) {
            display({
              "Only the first value will be considered.",
              "Executing \"config set " + arguments[1] + " " + arguments[2] + "\".",
              "",
            });
          }

          if (arguments.size() == 1) {
            display({"Please specify which configuration you want to set."});
          } else if (arguments.size() == 2) {
            display({"Please specify the value of \"" + arguments[1] + "\"."});
          } else {
            string key = arguments[1];
            string value = arguments[2];

            if (configurations.find(key) != configurations.end()) {
              configurations[key] = value;
              display({"\"" + key + "\" is now set to \"" + value + "\"."});
            } else {
              display({"There is no \"" + key + "\" in the configuration."});
            }
          }
        } else {
          display({"The supported operation is either \"get\" or \"set\"."});
        }
      }
    }},
    {"fetch", [&](vector<string> arguments) {
      if (arguments.size() == 0) {
        display({"Please specify what to fetch."});
      } else {
        string config = arguments[0];

        if (arguments.size() > 1) {
          display({
            "Only the first argument will be considered.",
            "Executing \"fetch " + config + "\".",
            "",
          });
        }

        if (config == "input") {
          if (inputs.size() > 0) {
            string action;

            cout << "  Doing this will refetch all input. Proceed? (y/N) ";
            getline(cin, action);

            if (action != "y") {
              return;
            } else {
              inputs.clear();
            }
          }

          Directory dir (configurations["input_path"]);
          dir.get_files();

          vector<string> failed_paths;

          for (File f : dir.list_files()) {
            pair<bool, string> p = f.fetch_content();

            if (p.first) {
              vector<string> path = split(f.get_path(), "/");
              string problem_code = split(path.back(), "_")[0];

              inputs[problem_code].push_back(f);
            } else {
              failed_paths.push_back(f.get_path());
            }
          }

          if (failed_paths.size() == 0) {
            display({"Inputs loaded."});
          } else {
            display({
              "Input(s) may not fully loaded.",
              "The following path(s) are failed to load:",
              "",
            });

            for (string path : failed_paths) {
              display({"  " + path});
            }
          }
        } else if (config == "output") {
          if (outputs.size() > 0) {
            string action;

            cout << "  Doing this will refetch all output. Proceed? (y/N) ";
            getline(cin, action);

            if (action != "y") {
              return;
            } else {
              outputs.clear();
            }
          }

          Directory dir (configurations["output_path"]);
          dir.get_files();

          vector<string> failed_paths;

          for (File f : dir.list_files()) {
            pair<bool, string> p = f.fetch_content();

            if (p.first) {
              vector<string> path = split(f.get_path(), "/");
              string problem_code = split(path.back(), "_")[0];

              outputs[problem_code].push_back(f);
            } else {
              failed_paths.push_back(f.get_path());
            }
          }

          if (failed_paths.size() == 0) {
            display({"Outputs loaded."});
          } else {
            display({
              "Output(s) may not fully loaded.",
              "The following path(s) are failed to load:",
              "",
            });

            for (string path : failed_paths) {
              display({"  " + path});
            }
          }
        } else if (config == "score") {
          if (scores.size() > 0) {
            string action;

            cout << "  Doing this will refetch all score. Proceed? (y/N) ";
            getline(cin, action);

            if (action != "y") {
              return;
            } else {
              scores.clear();
            }
          }

          Directory dir (configurations["score_path"]);
          dir.get_files();

          vector<string> failed_paths;

          for (File f : dir.list_files()) {
            pair<bool, string> p = f.fetch_content();

            if (p.first) {
              vector<string> path = split(f.get_path(), "/");

              scores[path.back()] = stoi(f.get_content());
            } else {
              failed_paths.push_back(f.get_path());
            }
          }

          if (failed_paths.size() == 0) {
            display({"Scores loaded."});
          } else {
            display({
              "Score(s) may not fully loaded.",
              "The following path(s) are failed to load:",
              "",
            });

            for (string path : failed_paths) {
              display({"  " + path});
            }
          }
        } else if (config == "submission") {
          if (submissions.size() > 0) {
            string action;

            cout << "  Doing this will refetch all submission. Proceed? (y/N) ";
            getline(cin, action);

            if (action != "y") {
              return;
            } else {
              submissions.clear();
            }
          }

          Directory dir (configurations["submission_path"]);
          dir.get_files();

          vector<string> failed_paths;

          for (File f : dir.list_files()) {
            pair<bool, string> p = f.fetch_content();

            if (p.first) {
              map<string, double> grades;
              for (pair<string, int> score : scores) {
                grades[score.first] = 0;
              }

              submissions.push_back({f, grades});
            } else {
              failed_paths.push_back(f.get_path());
            }
          }

          if (failed_paths.size() == 0) {
            display({"Submissions loaded."});
          } else {
            display({
              "Submission(s) may not fully loaded.",
              "The following path(s) are failed to load:",
              "",
            });

            for (string path : failed_paths) {
              display({"  " + path});
            }
          }
        } else {
          display({
            "There is no \"" + config + "\" in the configuration.",
            "So, nothing will be loaded.",
          });
        }
      }
    }},
    {"list", [&](vector<string> arguments) {
      if (arguments.size() == 0) {
        display({"Please specify what you want to display."});
      } else {
        if (arguments.size() > 1) {
          display({
            "Only the first argument will be considered.",
            "Executing \"list " + arguments[0] + "\".",
            "",
          });
        }

        string topic = arguments[0];

        if (topic == "config") {
          display({
            "---------------------------------------------------------------",
            "| Key                          | Value                        |",
            "---------------------------------------------------------------",
          });

          int char_cap = 28;

          for (pair<string, string> config : configurations) {
            string key = config.first;
            int key_size = int(key.size());
            string value = config.second;
            int value_size = int(value.size());

            for (int i = 0; i < char_cap - key_size; i++) {
              key += " ";
            }

            for (int i = 0; i < char_cap - value_size; i++) {
              value += " ";
            }

            display({"| " + key + " | " + value + " |"});
          }

          display({"---------------------------------------------------------------"});
        } else if (topic == "input") {
          display({
            "-----------------------------------",
            "| Problem Code | Input Files      |",
            "-----------------------------------",
          });

          int pc_cap = 12;
          int if_cap = 16;

          for (pair<string, vector<File>> input : inputs) {
            string problem_code = input.first;
            int pc_size = problem_code.size();
            vector<string> input_files;

            for (File f : input.second) {
              string filename = split(f.get_path(), "/").back();
              int f_size = filename.size();

              for (int i = 0; i < if_cap - f_size; i++) {
                filename += " ";
              }

              input_files.push_back(filename);
            }

            for (int i = 0; i < pc_cap - pc_size; i++) {
              problem_code += " ";
            }

            display({"| " + problem_code + " | " + input_files[0] + " |"});

            string whitespaces = "";
            for (int i = 0; i < pc_cap; i++) {
              whitespaces += " ";
            }

            for (int i = 1; i < int(input_files.size()); i++) {
              display({"| " + whitespaces + " | " + input_files[i] + " |"});
            }

            display({"-----------------------------------"});
          }
        } else if (topic == "output") {
          display({
            "-----------------------------------",
            "| Problem Code | Output Files     |",
            "-----------------------------------",
          });

          int pc_cap = 12;
          int if_cap = 16;

          for (pair<string, vector<File>> output : outputs) {
            string problem_code = output.first;
            int pc_size = problem_code.size();
            vector<string> output_files;

            for (File f : output.second) {
              string filename = split(f.get_path(), "/").back();
              int f_size = filename.size();

              for (int i = 0; i < if_cap - f_size; i++) {
                filename += " ";
              }

              output_files.push_back(filename);
            }

            for (int i = 0; i < pc_cap - pc_size; i++) {
              problem_code += " ";
            }

            display({"| " + problem_code + " | " + output_files[0] + " |"});

            string whitespaces = "";
            for (int i = 0; i < pc_cap; i++) {
              whitespaces += " ";
            }

            for (int i = 1; i < int(output_files.size()); i++) {
              display({"| " + whitespaces + " | " + output_files[i] + " |"});
            }

            display({"-----------------------------------"});
          }
        } else if (topic == "score") {
          display({
            "----------------------------",
            "| Problem Code | Max Score |",
            "----------------------------",
          });

          int pc_cap = 12;
          int ms_cap = 9;

          for (pair<string, int> score : scores) {
            string problem_code = score.first;
            int pc_size = problem_code.size();
            string max_score = to_string(score.second);
            int ms_size = max_score.size();

            for (int i = 0; i < pc_cap - pc_size; i++) {
              problem_code += " ";
            }

            for (int i = 0; i < ms_cap - ms_size; i++) {
              max_score += " ";
            }

            display({"| " + problem_code + " | " + max_score + " |"});
          }

          display({"----------------------------"});
        } else if (topic == "submission") {
          string border = "----------------------------------";
          string header = "| ID  | Submission Name          |";

          map<string, int> s_caps;

          for (pair<string, int> score : scores) {
            string problem_code = score.first;
            int pc_size = problem_code.size();

            s_caps[problem_code] = pc_size + 4;

            for (int i = 0; i < pc_size + 7; i++) {
              border += "-";
            }

            problem_code += "  ";
            header += " " + problem_code + "   |";
          }

          display({
            border,
            header,
            border,
          });

          int id_cap = 3;
          int sn_cap = 24;

          int id = 1;
          for (pair<File, map<string, double>> submission : submissions) {
            string filename = split(submission.first.get_path(), "/").back();
            int f_size = filename.size();
            string ids = to_string(id);
            int ids_size = ids.size();

            for (int i = 0; i < id_cap - ids_size; i++) {
              ids += " ";
            }

            for (int i = 0; i < sn_cap - f_size; i++) {
              filename += " ";
            }

            string scores = "";

            for (pair<string, double> grade : submission.second) {
              string problem_code = grade.first;

              ostringstream oss;
              oss << fixed << setprecision(2) << grade.second;

              string score = oss.str();
              int s_size = score.size();

              for (int i = 0; i < s_caps[problem_code] - s_size; i++) {
                score += " ";
              }

              scores += " " + score + " |";
            }

            display({"| " + ids + " | " + filename + " |" + scores});
            id += 1;
          }

          display({border});
        } else {
          display({
            "There is no \"list " + topic + "\".",
            "Please use \"help\" to see the valid command.",
          });
        }
      }
    }},
    {"judge", [&](vector<string> arguments) {
      if (arguments.size() == 0) {
        display({"Please specify the submission ID."});
        return;
      }

      int submission_id = stoi(arguments[0]) - 1;

      if (submission_id < 0 || submission_id >= submissions.size()) {
        display({"Submission with ID " + to_string(submission_id + 1) + " does not exists."});
        return;
      }

      if (arguments.size() == 1) {
        display({"Please specify which problem you want to judge."});
        return;
      }

      int idx = 1;
      set<string> problem_codes;

      if (arguments[1] == "all") {
        for (pair<string, int> score : scores) {
          problem_codes.insert(score.first);
        }

        idx = 2;
      }

      for (int i = idx; i < int(arguments.size()); i++) {
        problem_codes.insert(arguments[i]);
      }

      pair<File, map<string, double>> submission = submissions[submission_id];
      string submission_path = submission.first.get_path();
      string submission_name = split(submission_path, "/").back();

      display({"Judging \"" + submission_name + "\""});

      for (string problem_code : problem_codes) {
        display({"  Taking problem \"" + problem_code + "\"."});

        vector<File> input;
        vector<File> expected_output;

        if (inputs.find(problem_code) != inputs.end()) {
          input = inputs[problem_code];
        }

        if (outputs.find(problem_code) != outputs.end()) {
          expected_output = outputs[problem_code];
        }

        bool is_skip = false;

        if (input.size() == 0) {
          display({"    Input for this problem is empty."});
          is_skip = true;
        }

        if (expected_output.size() == 0) {
          display({"    Expected output for this problem is empty."});
          is_skip = true;
        }

        if (input.size() != expected_output.size()) {
          display({"    The number of input and expected output is not the same."});
          is_skip = true;
        }

        if (is_skip) {
          display({"    Skipping this problem."});
        } else {
          int correct = 0;
          int testcases = input.size();
          int max_score = scores[problem_code];

          for (int i = 0; i < testcases; i++) {
            string testcase_name = split(split(input[i].get_path(), "/").back(), ".")[0];

            cout << "      Result for \"" + testcase_name + "\": ";

            string in = input[i].get_content();
            string exp_out = expected_output[i].get_content();

            string command = "/usr/bin/timeout 2 /bin/sh -c ";
            command += "\"swipl -q -g '" + in + "' -t 'halt.' -f " + submission_path + "\"";

            try {
              pair<int, string> process = exec(command.c_str());

              if (process.first == 0) {
                bool is_correct = process.second == exp_out;
                correct += is_correct;

                cout << (is_correct ? "AC" : "WA") << endl;
              } else if (process.first == 31744) {
                cout << "TLE" << endl;
              } else {
                if (process.second.size() == 0) {
                  cout << "WA" << endl;
                } else {
                  bool is_correct = process.second == exp_out;
                  correct += is_correct;

                  cout << (is_correct ? "AC" : "WA") << endl;
                }
              }
            } catch (const runtime_error& e) {
              cout << "RTE (can't open the file)" << endl;
            } catch (...) {
              cout << "RTE (unkown error)" << endl;
            }
          }

          double score = (correct / double(testcases)) * max_score;
          submissions[submission_id].second[problem_code] = score;

          ostringstream oss;
          oss << fixed << setprecision(2) << score;

          display({"  Scored " + oss.str() + " out of " + to_string(max_score)});
        }
      }
    }},
  };

  do {
    cout << "grode> ";
    getline(cin, input);

    if (input.size() == 0) {
      continue;
    }

    vector<string> formatted_input = split(input, " ");
    string command = formatted_input[0];
    vector<string> arguments = vector<string>(formatted_input.begin() + 1, formatted_input.end());

    if (supported_commands.find(command) != supported_commands.end()) {
      supported_commands[command](arguments);
    } else {
      display({
        "Command \"" + command + "\" is not supported.",
        "Please use \"help\" command to see the list of supported commands.",
      });
    }
  } while (input != "exit" && !cin.eof());

  if (cin.eof()) {
    cout << "exit" << endl;
  }

  return 0;
}

void display(vector<string> messages) {
  for (int i = 0; i < int(messages.size()); i++) {
    cout << "  " << messages[i] << endl;
  }
}

vector<string> split(string str, string de) {
  size_t pos = 0;
  string token;

  vector<string> ret;

  while ((pos = str.find(de)) != string::npos) {
    token = str.substr(0, pos);
    ret.push_back(token);

    str.erase(0, pos + de.length());
  }

  ret.push_back(str);
  return ret;
}

pair<int, string> exec(const char* cmd) {
  array<char, 128> buffer;
  string result;

  auto pipe = popen(cmd, "r");

  if (!pipe) {
    throw runtime_error("popen() failed!");
  }

  while (!feof(pipe)) {
    if (fgets(buffer.data(), 128, pipe) != nullptr) {
      result += buffer.data();
    }
  }

  pair<int, string> ret = {pclose(pipe), result};

  return ret;
}
