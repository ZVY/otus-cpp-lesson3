#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector> 
#include <fstream>  
#include <sstream>
#include <algorithm>

struct IpAddress
{
	int part1;
	int part2;
	int part3;
	int part4;	

	std::string printIP()
	{
		return std::to_string(part1) + "." + std::to_string(part2) + "." + std::to_string(part3) + "." + std::to_string(part4);
	}	
};

IpAddress getIP(const std::string &row, char separator)
{	
	std::string::size_type start = 0;
	std::string::size_type stop  = row.find_first_of(separator);
	std::string ip = (row.substr(0, stop - start));
	
	int posEnd = 0;
	auto sepIP = [&](const std::string &str_ip, int posBeg) -> int
	{		
		posEnd = str_ip.find('.', posBeg);
		return atoi(str_ip.substr(posBeg, posEnd).c_str());
	};
	
	return { sepIP(ip,0), sepIP(ip, posEnd + 1), sepIP(ip, posEnd + 1), sepIP(ip, posEnd + 1) };
}

void reverseLexSort(std::vector<IpAddress> &ip_pool)
{	
	std::sort(ip_pool.begin(), ip_pool.end(), [](const IpAddress &a, const IpAddress &b) -> bool
	{
		if ((a.part1 > b.part1))
			return true;
		else if ((a.part1 == b.part1))
		{
			if ((a.part2 > b.part2))
				return true;
			else if ((a.part2 == b.part2))
			{
				if ((a.part3 > b.part3))
					return true;
				else if ((a.part3 == b.part3))
					return ((a.part4 > b.part4));
			}    
		}

		return false;
	});
}

std::string getIPPool(const std::vector<IpAddress>& ip_pool)
{
	std::string msg;
	for (auto ip : ip_pool)
	{
		msg += ip.printIP() + "\n";
	}

	return msg;
}

std::string filter(std::vector<IpAddress> &ip_pool, size_t number)
{	
	std::string msg;
	for (auto ip : ip_pool)
	{
		if (ip.part1 == number)
			msg += ip.printIP() + "\n";
	}

	return msg;
}

std::string filter(std::vector<IpAddress> &ip_pool, size_t number1, size_t number2)
{
	std::string msg;
	for (auto ip : ip_pool)
	{
		if ((ip.part1 == number1) && (ip.part2 == number2))
			msg += ip.printIP() + "\n";
	}

	return msg;
}

std::string filter_any(std::vector<IpAddress> &ip_pool, size_t number)
{	
	std::string msg;
	for (auto ip : ip_pool)
	{
		if ((ip.part1 == number) || (ip.part2 == number) || (ip.part3 == number) || (ip.part4 == number))
			msg += ip.printIP() + "\n";
	}

	msg.erase(msg.end()-1);

	return msg;
}

int main(int argc, char const *argv[])
{
	try
	{	
		std::ifstream ifs(argv[1]);
		std::vector<IpAddress> ip_pool;	
		
		for (std::string line; std::getline(std::cin, line);)
		{
			if (!std::string(line).empty())
			{
				ip_pool.emplace_back(getIP(line, '\t'));
			}
		}		
		
		reverseLexSort(ip_pool);

		std::cout << getIPPool(ip_pool);
		std::cout << filter(ip_pool, 1);
		std::cout << filter(ip_pool, 46, 70);
		std::cout << filter_any(ip_pool, 46);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	//system("pause");

	return 0;
}