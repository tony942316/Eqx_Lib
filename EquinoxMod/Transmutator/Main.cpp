import Equinox;

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

std::string pruneMod(std::stringstream& file)
{
    auto result = std::string{};
    auto temp = std::string{};

    while (!file.eof())
    {
        std::getline(file, temp);
        if (temp.find("module;"sv) != std::string::npos)
        {
            temp = "#ifndef EQX_POINT_123\n"sv
                "#define EQX_POINT_123\n"sv
                "\n"sv
                "#include <stdh.hpp>\n"sv;
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

        result += temp;
        result += '\n';
    }

    result += "#endif // Guard"sv;

    return result;
}

int main()
{
    std::cout << "Start\n\n"sv;

    auto root = std::filesystem::path{
        "/home/anthony/C++/Equinox/EquinoxMod/EquinoxHol/"sv };
    auto modRoot = std::filesystem::path{
        "/home/anthony/C++/Equinox/EquinoxMod/Equinox/"sv };

    std::filesystem::copy(modRoot, root,
        std::filesystem::copy_options::recursive);

    std::cout << "\nEnd: "sv;
    std::cin.get();
    return 0;
}
