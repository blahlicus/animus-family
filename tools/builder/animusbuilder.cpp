#include <sys/stat.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#ifdef _WIN32
   //#include <windows.h>
#else
  //define it for a Unix machine
#endif

bool IsNumeric(std::string input)
{
  bool output = true;
  for (int i = 0; i < input.size(); i++)
  {
    if (isdigit(input[i]))
    {
      // do nothing
    }
    else
    {
      output = false;
    }
  }
  return output;
}

bool IsArray(std::string input)
{
  for (int i = 0; i < input.size(); i++)
  {
    if (isalnum(input[i]) || input[i] == ' ' || input[i] == ',')
    {
      // do nothing
    }
    else
    {
      return false;
    }
  }

  while (input.front() == ' ')
  {
    input.erase(0, 1);
  }

  while (input.back() == ' ')
  {
    input.pop_back();
  }

  if (input.front() == ',' || input.back() == ',')
  {
    return false;
  }

  while (input.find(',') != std::string::npos && input.find_first_of(',') != 0)
  {
    std::cout << input.find(',');
    while (input[input.find(',')-1] == ' ' && input.find(',')-1 != -1)
    {
      input.erase(input.find(',')-1, 1);
    }
    while (input[input.find(',')+1] == ' ' && input.find(',')+1 != -1)
    {
      input.erase(input.find(',')+1, 1);
    }

    if (input[input.find(',') + 1] == ',')
    {
      return false;
    }
    if (input.find(',') != std::string::npos)
    {
      input.erase(input.find(','), 1);
    }
  }

  if (input.find(' ') != -1)
  {
    return false;
  }

  return true;
}

bool IsModArray(std::string input)
{
  if (IsArray(input))
  {
    while (input.find(' ') != -1)
    {
      input.erase(input.find(' '), 1);
    }
    std::string temp = input;
    int counter = 0;
    if (temp.find('.') == -1)
    {
      return false;
    }
    while (temp.find('.'))
    {
      counter++;
      temp.erase(temp.find('.'), 1);
    }
    std::string arr [counter];
    temp = input;
    for (int i = 0; i < counter; i++)
    {
      arr[i] = temp.substr(0, temp.find('.') + 4);
      temp = temp.substr(temp.find('.') + 4);

      if (arr[i].find("mod_") != 0)
      {
        return false;
      }

      if (arr[i].find(".ino") != temp.find('.'))
      {
        return false;
      }
    }

    return true;
  }
}
void SetFileAttribute(std::string file, std::string attr, std::string val)
{
  std::vector<std::string> output;
  std::ifstream src(file.c_str());
  std::string temp;


  if (!src)
  {
    return;
  }

  while (std::getline(src, temp))
  {
    output.push_back(temp);
  }
  src.close();
  std::ofstream outputfile;
  outputfile.open(file.c_str(), std::ios::trunc);
  for (int i = 0; i < output.size(); i++)
  {
    if (output[i].find("#define " + attr) == 0)
    {
      output[i] = "#define " + attr + " """"""""" + val;
    }
    outputfile << output[i] << std::endl;
  }
  outputfile.close();
}

bool IsAlphanumericOrSpace(std::string input)
{
  bool output = true;
  for (int i = 0; i < input.size(); i++)
  {
    if (isalnum(input[i]) || input[i] == ' ')
    {
      // do nothing
    }
    else
    {
      output = false;
    }
  }
  return output;
}

inline bool FileOrDirectoryExists(const std::string & input)
{
  struct stat buffer;
  return (stat(input.c_str(), &buffer) == 0);
}


inline std::string GetPathFromCin()
{
  std::string output = "";
  std::cin >> output;
  while (!FileOrDirectoryExists(output))
  {
    std::cout << "Error: Directory or file does not exist. reenter :";
    std::cin >> output;
  }
  return output;
}


std::string GetDirectoryFromPathname (std::string input)
{
  size_t found;
  found=input.find_last_of("/\\");
  return input.substr(0,found);
}

void DirectoryCopy(std::string input, std::string output)
{
  #ifdef _WIN32
    system(("xcopy " + input + " " + output + " /E /H /I /Y").c_str());
  #else
    system(("cp -rf " + input + " " + output).c_str());
  #endif
}

void DirectoryCreate(std::string input)
{
  if (!FileOrDirectoryExists(input))
  {
    #ifdef _WIN32
      system(("mkdir " + input).c_str());
    #else
      system(("mkdir -p " + input).c_str());
    #endif
  }

}

void FileCopy(std::string input, std::string output)
{
  DirectoryCreate(GetDirectoryFromPathname(output));
  std::ifstream src(input, std::ios::binary);
  std::ofstream dst(output, std::ios::binary);
  dst << src.rdbuf();
}

int main(int argc, char* argv[])
{
  std::string animus_path;
  std::string output_path;
  std::string builder_row;
  std::string builder_col;
  std::string builder_vpins;
  std::string builder_hpins;
  std::string builder_refresh = "10";
  std::string builder_kbname = "Unknown Animus Device";
  std::string builder_kbvariant = "Unknown Animus Device";
  std::string builder_kbdriver;
  std::string builder_kbdriver_build;
  std::string mod_path;
  std::string builder_modlist;
  std::string builder_kbinfo;

  std::string mainfile_path;
  std::string modfile_path;

  if (argc < 7)
  {
    if (argc == 1)
    {
      SetFileAttribute("C:\\Users\\blahlicus\\Documents\\GitHub\\animus-family\\animus\\animusmaster\\animusmaster.ino", "builder_kbinfo", "blahblah");
    }
    if (argc == 2)
    {
      std::string help = argv[1];
      if (help == "help")
      {
        std::cout << "Help menu" << std::endl
        << "animusbuilder accepts several argument orders" << std::endl
        << "1) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins]" << std::endl << std::endl
        << "2) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh]" << std::endl << std::endl
        << "3) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh]" << std::endl << std::endl
        << "4) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh] [-str kbname] [-str kbvariant] [-str kbdriver build]" << std::endl << std::endl
        << "5) animusbuilder [-str animus path] [-str output path] [-int row] [-int col] [-arr<pins> vpins] [-arr<pins> hpins] [-int refresh] [-str kbname] [-str kbvariant] [-str kbdriver build] [-str mod path] [-arr<str mod filename>  modlst]" << std::endl << std::endl
        << "-str denotes a string input such as \"abc\"" << std::endl
        << "-int denotes an integer input such as 123" << std::endl
        << "-int denotes an arduino pin input such as 5 or A0" << std::endl
        << "-arr<t> denotes an array of type t" << std::endl
        << "arrays are declared without brackets, separated with commas, and surrounded by quotes" << std::endl
        << "example array -arr<pins>:\"2, 3, A2, A3, A4\"" << std::endl
        << "example array -arr<str>: \"abc, def, ghi\"" << std::endl;
      }
    }
    std::cout << "Error: incorrect number of arguments! use help as argument for more information!" << std::endl;
    exit(-1);
  }
  if (argc > 6)
  {
    animus_path = argv[1];
    output_path = argv[2];
    builder_row = argv[3];
    builder_col = argv[4];
    builder_vpins = argv[5];
    builder_hpins = argv[6];

    if (animus_path[animus_path.size()-1] == '\\' || animus_path[animus_path.size()-1] == '/')
    {
      animus_path = animus_path.substr(0, animus_path.size()-2);
    }

    if (!FileOrDirectoryExists(animus_path))
    {
      std::cout << "Error: animus path: " << animus_path << " does not exist!" << std::endl;
      exit(-1);
    }
    #ifdef _WIN32
    std::string maindriver = animus_path.substr(animus_path.find_last_of('\\'));
    #else
    std::string maindriver = animus_path.substr(animus_path.find_last_of('/'));
    #endif

  	const int checkerSize = 2;

    #ifdef _WIN32
  	std::string checker[2] = { maindriver + ".ino", "\\mod.ino" };
    #else
  	std::string checker[2] = { maindriver + ".ino", "/mod.ino" };
    #endif

  	for (int i = 0; i < checkerSize ; i++)
  	{
  		if (FileOrDirectoryExists(animus_path + checker[i]))
  		{
  			std::cout << checker[i] << " OK!" << std::endl;
  		}
  		else
  		{
  			std::cout << checker[i] << " Does not exists!" << std::endl;
  			std::cout << "Error: File does not exist, now exiting";
        exit(-1);
  		}
  	}

    DirectoryCopy(animus_path, output_path);
    mainfile_path = output_path + maindriver + ".ino";
    #ifdef _WIN32
    modfile_path = output_path + "\\mod.ino";
    #else
    modfile_path = output_path + "/mod.ino";
    #endif
    if (!IsNumeric(builder_row))
    {
      std:: cout << "Error: builder row: " << builder_row << " is not numeric!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder row OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_row", builder_row);
    }

    if (!IsNumeric(builder_col))
    {
      std:: cout << "Error: builder col: " << builder_col << " is not numeric!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder col OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_col", builder_col);
    }

    if (!IsArray(builder_vpins))
    {
      std:: cout << "Error: builder vpins: " << builder_vpins << " is not a valid array!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder vpins OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_vpins", builder_vpins);
    }

    if (!IsArray(builder_hpins))
    {
      std:: cout << "Error: builder hpins: " << builder_hpins << " is not a valid array!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder hpins OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_hpins", builder_hpins);
    }
  }
  if (argc > 7)
  {
    builder_refresh = argv[7];
    if (!IsNumeric(builder_refresh))
    {
      std:: cout << "Error: builder refresh: " << builder_refresh << " is not numeric!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder refresh rate OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_refresh", builder_refresh);
    }
  }
  if (argc > 10)
  {
    builder_kbname = argv[8];
    builder_kbvariant = argv[9];
    builder_kbdriver_build = argv[10];;
    if (!IsAlphanumericOrSpace(builder_kbname))
    {
      std:: cout << "Error: builder kbname: " << builder_kbname << " is not alphanumeric!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder kbname OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_kbname", "\"" + builder_kbname + "\"" );
    }
    if (!IsAlphanumericOrSpace(builder_kbvariant))
    {
      std:: cout << "Error: builder kbvariant: " << builder_kbvariant << " is not alphanumeric!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder kbvariant OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_kbvariant", "\"" + builder_kbvariant + "\"" );
    }
    if (!IsAlphanumericOrSpace(builder_kbdriver_build))
    {
      std:: cout << "Error: builder driver build: " << builder_kbdriver_build << " is not alphanumeric!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder driver build OK!" << std::endl;
      SetFileAttribute(mainfile_path, "builder_kbdriver_build", "\"" + builder_kbdriver_build + "\"" );
    }


  }
  if (argc > 12)
  {
    mod_path = argv[11];
    builder_modlist = argv[12];

    if (mod_path[mod_path.size()-1] == '\\' || mod_path[mod_path.size()-1] == '/')
    {
      mod_path = mod_path.substr(0, mod_path.size()-2);
    }
    if (!FileOrDirectoryExists(mod_path))
    {
      std::cout << "Error: mod path: " << mod_path << " does not exist!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "mod path OK!" << std::endl;
    }

    if (!IsModArray(builder_modlist))
    {
      std:: cout << "Error: builder modlist: " << builder_modlist << " is not a valid mod list!" << std::endl;
      exit(-1);
    }
    else
    {
      std:: cout << "Builder modlist OK!" << std::endl;
    }


    std::string temp = builder_modlist;
    int counter = 0;
    std::cout << temp << std::endl;
    while (temp.find('.')!=-1  && temp.find('.') <temp.size())
    {
      counter++;
      temp.erase(temp.find('.'), 1);
    }
    std::string arr [counter];
    temp = builder_modlist;
    std::string builder_mstartup = "";
    std::string builder_mloop = "";
    std::string builder_mkeydown = "";
    std::string builder_mkeyup = "";
    std::string builder_mserial = "";
    for (int i = 0; i < counter; i++)
    {
      std::string modfilename = temp.substr(0, temp.find('.') + 4);
      std::string modname = temp.substr(4, temp.find('.')-4);
      std::cout << modname << std::endl;

      builder_mstartup = builder_mstartup + modname + "Startup(); ";
      builder_mloop = builder_mloop + modname + "Loop(); ";
      builder_mkeydown = builder_mkeydown + modname + "KeyDown(val, type); ";
      builder_mkeyup = builder_mkeyup + modname + "KeyUp(val, type); ";
      builder_mserial = builder_mserial + modname + "Serial(input); ";


      #ifdef _WIN32
      arr[i] = mod_path + "\\" + temp.substr(0, temp.find('.') + 4);
      std::string outputfile = output_path + "\\" + temp.substr(0, temp.find('.') + 4);
      #else
      arr[i] = mod_path + "/" + temp.substr(0, temp.find('.') + 4);
      std::string outputfile = output_path + "/" + temp.substr(0, temp.find('.') + 4);
      #endif
      temp = temp.substr(temp.find("mod_") +3);
      if (temp.find("mod_") !=-1)
      {

        temp = temp.substr(temp.find("mod_"));
      }
      if (!FileOrDirectoryExists(arr[i]))
      {
        std:: cout << "Error: the mod file: " << arr[i] << " does not exist!" << std::endl;
        exit(-1);
      }
      else
      {
        std:: cout << "Adding mod: " << modname << std::endl;
        SetFileAttribute(modfile_path, "builder_mstartup", builder_mstartup);
        SetFileAttribute(modfile_path, "builder_mloop", builder_mloop);
        SetFileAttribute(modfile_path, "builder_mkeydown", builder_mkeydown);
        SetFileAttribute(modfile_path, "builder_mkeyup", builder_mkeyup);
        SetFileAttribute(modfile_path, "builder_mserial", builder_mserial);

        FileCopy(arr[i],outputfile);
      }
    }



  }
  return 0;
}
