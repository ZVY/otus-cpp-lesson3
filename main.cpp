#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>

std::vector<int> getIP(const std::string &row, char separator)
{
	std::string::size_type start = 0;
	std::string::size_type stop = row.find_first_of(separator);
	std::string ip = (row.substr(0, stop - start));

	int posEnd = 0;
	auto sepIP = [&](const std::string &str_ip, int posBeg) -> int
	{
		posEnd = str_ip.find('.', posBeg);
		return atoi(str_ip.substr(posBeg, posEnd).c_str());
	};

	return { sepIP(ip,0), sepIP(ip, posEnd + 1), sepIP(ip, posEnd + 1), sepIP(ip, posEnd + 1) };
}

void printIP(const std::vector<int> &ip)
{
	size_t size = ip.size();
	for (size_t i = 0; i < size; ++i)
		std::cout << ip[i] << ((i < size - 1) ? "." : "\n");
}

void printIPPool(const std::vector<std::vector<int>>& ip_pool)
{	
	for (auto ip : ip_pool)
	{
		printIP(ip);
	}
}

void printFilter(const std::vector<std::vector<int>>& ip_pool, int octet1)
{
	for (auto ip : ip_pool)
	{
		if (ip[0] == octet1)
		{
			printIP(ip);
		}
	}
}

void printFilter(const std::vector<std::vector<int>>& ip_pool, int octet1, int octet2)
{
	for (auto ip : ip_pool)
	{
		if ((ip[0] == octet1) && (ip[1] == octet2))
		{
			printIP(ip);
		}
	}
}

void printFilterAny(const std::vector<std::vector<int>>& ip_pool, int req_octet)
{	
	std::vector<std::vector<int>> vec{ {23,45,28,45}, {1,46,78,66}, {4,99,245,47}, {46,99,245,47}, {4,46,275,46} };
	for (auto ip : vec)
	{
		if (std::any_of(ip.begin(), ip.end(), [=](int octet) { return octet == req_octet; }))
		{
			printIP(ip);
		}
	}
}

int main(int, char const **)
{
	try
	{	
		std::vector<std::vector<int>> ip_pool;
		/*for (std::string line; std::getline(std::cin, line);)
		{
			if (!std::string(line).empty())
			{
				ip_pool.emplace_back(getIP(line, '\t'));
			}
		}

		std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());

		printIPPool(ip_pool);
		printFilter(ip_pool, 1);
		printFilter(ip_pool, 46, 70);*/
		printFilterAny(ip_pool, 46);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");

	return 0;
}