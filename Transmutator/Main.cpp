#include <Stdh/std.hpp>

import Eqx.Lib;

constexpr auto GPL3 = std::string_view{
 "/*\n"sv
 " * Copyright (C) 2024 Anthony H. Grasso\n"sv
 " *\n"sv
 " * This program is free software: you can redistribute it and/or modify\n"sv
 " * it under the terms of the GNU General Public License as published by\n"sv
 " * the Free Software Foundation, either version 3 of the License, or\n"sv
 " * (at your option) any later version.\n"sv
 " *\n"sv
 " * This program is distributed in the hope that it will be useful,\n"sv
 " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"sv
 " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"sv
 " * GNU General Public License for more details.\n"sv
 " *\n"sv
 " * You should have received a copy of the GNU General Public License\n"sv
 " * along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"sv
 " */"sv };

void license(const std::string_view file)
{
    auto s = file.find("/*"sv);
    auto e = file.find("*/"sv);
    auto li = file.substr(s, e + 2);
    std::cout << (GPL3 == li) << std::endl;
}

std::string getParentDir(const std::filesystem::path& path)
{
    auto pos = path.parent_path().string().rfind('/');
    return path.parent_path().string().substr(pos + 1);
}

void convertModule(const std::filesystem::path& path)
{
    auto fileKey = "EQX_"s;
    fileKey += getParentDir(path);
    fileKey += '_';
    fileKey += path.stem().string();
    fileKey += '_';
    fileKey += "123"sv;

    auto file = std::ifstream{path.string(), std::ios::in};
    auto newPath = path;
    newPath.replace_extension(".hpp"sv);
    auto newFile = std::ofstream(newPath.string(),
        std::ios::out | std::ios::trunc);

    auto temp = std::string{};

    while (!file.eof())
    {
        std::getline(file, temp);
        if (temp.find("module;"sv) != std::string::npos
            || temp.find("#include") != std::string::npos)
        {
            temp = "";
        }
        else if (temp.find("import") != std::string::npos)
        {
            if (temp.find("Eqx.Stdm") != std::string::npos)
            {
                temp = "#include <stdh.hpp>";
                if (path.stem() == "Misc"sv)
                {
                    temp += "\n#include <Equinox/Macros.hpp>";
                }
            }
            else if (temp.find("Eqx.OSm") != std::string::npos)
            {
                temp = "#include <osh.hpp>";
            }
            else
            {
                if (temp.find("export import") != std::string::npos)
                {
                    temp.replace(0, 14, "#include <");
                }
                else
                {
                    temp.replace(0, 7, "#include <");
                }
                std::ranges::replace(temp, '.', '/');
                temp.pop_back();
                if (std::ranges::count(temp, '/') == 1)
                {
                    temp += temp.substr(temp.find('/'));
                }
                temp += ".hpp>"sv;
            }
        }
        else if (temp.find("export module") != std::string::npos)
        {
            temp = "#ifndef "sv;
            temp += fileKey;
            temp += '\n';

            temp += "#define "sv;
            temp += fileKey;
            temp += '\n';
        }
        else if (temp.find("module"sv) != std::string::npos
            || temp.find("import"sv) != std::string::npos)
        {
            temp = "";
        }
        else if (temp.find("export"sv) != std::string::npos)
        {
            temp.replace(temp.find("export "sv), 7, ""sv);
        }

        newFile << temp << '\n';
    }

    newFile << "#endif // "sv << fileKey;
}

int main()
{
    std::cout << "Start\n\n"sv;

    auto root = std::filesystem::path{
        "/home/anthony/C++/Equinox/"sv };
    auto hol = std::filesystem::path{
        root / "EquinoxHol/include/Equinox/"sv };
    auto mod = std::filesystem::path{
        root / "EquinoxMod/"sv };
    auto transmutator = std::filesystem::path{
        root / "Transmutator/"sv };

    std::filesystem::remove_all(root / "EquinoxHol/"sv);

    std::filesystem::create_directory(root / "EquinoxHol/"sv);
    std::filesystem::create_directory(root / "EquinoxHol/include/"sv);
    std::filesystem::create_directory(root / "EquinoxHol/include/Equinox/"sv);

    std::filesystem::copy(mod, hol,
        std::filesystem::copy_options::recursive
        | std::filesystem::copy_options::overwrite_existing);

    std::filesystem::copy(hol / "include/Equinox/Macros.hpp"sv,
        hol / "Macros.hpp"sv,
        std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(transmutator / "holcml.txt"sv,
        hol / "CMakeLists.txt"sv,
        std::filesystem::copy_options::overwrite_existing);

    std::filesystem::remove_all(hol / "include/"sv);

    auto dir = std::filesystem::recursive_directory_iterator{hol};
    for (const auto& entry : dir)
    {
        if (entry.path().extension() == ".cpp"sv)
        {
            std::cout << "Converting: "
                << getParentDir(entry.path())
                << entry.path().filename() << '\n';
            convertModule(entry.path());
            std::filesystem::remove(entry.path());
        }
    }

    std::cout << "\nEnd: "sv;
    std::cin.get();
    return 0;
}
