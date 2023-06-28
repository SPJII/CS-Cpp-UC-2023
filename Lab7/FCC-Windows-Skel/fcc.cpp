
#include <fstream>
#include <iostream>
#include <vector>


bool more_to_read(std::ifstream &file) {
  file >> std::noskipws;
  while (file.peek() == ' ') {
    char discard;
    file >> discard;
  }
  return !(file.eof() || std::iscntrl(file.peek()));
}

std::vector<std::string> read(const std::string &filename) {
  std::vector<std::string> words;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    return words;
  }
  while (more_to_read(file)) {
    std::string word;
    file >> word;
    words.push_back(word);
  }
  file.close();
  return words;
}


int fcc(const std::string &fixme_filename, const std::string &typo_filename,
        const std::string &fixo_filename, std::string &fixed_sentence) 
      {
      std::vector<std::string> fixme_words = read(fixme_filename);
      std::vector<std::string> typo_words = read(typo_filename);
      std::vector<std::string> fixo_words = read(fixo_filename);

      int typofix{0};
    
      if (typo_words.size() != fixo_words.size()) 
        {
        std::cerr << "Error: the number of words in the files do not match" << std::endl;
          return 1;
        }
      for (int i = 0; i < fixme_words.size(); i++)  
        {
        for (int j = 0; j < typo_words.size(); j++) 
          {
          if (fixme_words[i] == typo_words[j]) 
            {
            fixme_words[i] = fixo_words[j];
            typofix++;
            }
          }
        }

      for (int i = 0; i < fixme_words.size(); i++) 
        {
        fixed_sentence += fixme_words[i] + " ";
        }
        fixed_sentence[fixed_sentence.size() - 1] = '.';
        return typofix;
      }
/*
 * <fixme_filename>
 *
 * <Read in the input from the fixos file and the typos file>
 *
 * input: <typo_filename>
 * output: <typo_sentence>
 */
void read_in_typos(const std::string &typo_filename,
                   std::string &typo_sentence) {
  std::ifstream file(typo_filename);
  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << typo_filename << std::endl;
    return;
  }
  while (more_to_read(file)) {
    std::string word;
    file >> word;
    typo_sentence += word + " ";
  }
  file.close();

}

/*
 * <typo_filename>
 *
 * <search for the typo in the fixme file and replace it with the fixo>
 * 
 * input: <typo_sentence>
 * output: <fixed_sentence>
 */

void fix_typos(const std::string &typo_sentence, const std::string &fixme_filename,
               const std::string &fixo_filename, std::string &fixed_sentence) {
  std::ifstream file(fixme_filename);
  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << fixme_filename << std::endl;
    return;
  }
  while (more_to_read(file)) {
    std::string word;
    file >> word;
    if (word == typo_sentence) {
      fixed_sentence += fixo_filename + " ";
    } else {
      fixed_sentence += word + " ";
    }
  }
  file.close();

}

/*
 * <expected_number_of_fixes>
 *
 * <compare the fixed sentence to the expected sentence>
 * 
 * input: <fixed_sentence>
 * output: <expected_sentence>
 */

void compare(const std::string &fixed_sentence, const std::string &expected_sentence) {
  if (fixed_sentence == expected_sentence) {
    std::cout << "Success!" << std::endl;
  } else {
    std::cout << "Failure!" << std::endl;
  }
}

/*
 * <main>
 *
 * <call the functions>
 * 
 * input: <fixme_filename>, <typo_filename>, <fixo_filename>, <expected_sentence>
 * output: <fixed_sentence>
 */

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " <fixme_filename> <typo_filename> <fixo_filename> <expected_sentence>" << std::endl;
    return -1;
  }
  std::string fixme_filename = argv[1];
  std::string typo_filename = argv[2];
  std::string fixo_filename = argv[3];
  std::string expected_sentence = argv[4];
  std::string fixed_sentence;
  std::string typo_sentence;
  read_in_typos(typo_filename, typo_sentence);
  fix_typos(typo_sentence, fixme_filename, fixo_filename, fixed_sentence);
  compare(fixed_sentence, expected_sentence);
  return 0;

}


