// MapleMini.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MapleMini.h"

void header()
{
	WriteLineBold("MapleSeed CLI Version %4.2f", 1.05);
	WriteLineBold("Built: %s @ %s\n", __DATE__, __TIME__);
}

po::options_description defineOptions()
{
	po::options_description desc("Command line examples");
	desc.add_options()
		("help", "produce help message")
		("tik", po::value<string>()->value_name("000500001011c100"), "create tmd and cetk using title id")
		("dl", po::value<string>()->value_name("000500001011c100"), "download content using a title id")
		("de", po::value<string>()->value_name("\"c:\\path\\to\\enc\\\""), "decrypt content. requires tmd")
		;
	return desc;
}

void simpleDecrypt(std::string path, std::string defaultdir)
{
	_chdir(path.c_str());

	if (!FileExists(".\\tmd"))
	{
		WriteLineRed("tmd file is missing. Decryption failed!");
		return;
	}

	if (!FileExists(".\\cetk"))
	{
		WriteLineRed("cetk file is missing. Decryption failed!");
		return;
	}

	startDecryption(3, "tmd", "cetk", 0);
	_chdir(defaultdir.c_str());
}

void downloadcontent(std::string defaultdir, std::string id)
{
	WriteLine("Downloading title information for %s", id.c_str());
	string url = string("http://api.tsumes.com/title/" + id);
	auto jd = DownloadBytes(url.c_str());
	if (jd.data == nullptr) return;

	auto ti = TitleInfo(jd.data, jd.len);
	if (ti.id != NULL)
	{
		WriteLine("Downloading content for '[%s] %s'", ti.region, ti.name);
		ti.DownloadContent();

		simpleDecrypt(ti.workingDir.c_str(), defaultdir.c_str());
	}
	else
	{
		WriteLine("Downloading title information failed, id %s not valid", id.c_str());
	}
}

void create_decrypt_file(std::string _id)
{
	auto id = _id.c_str();
	auto ti = TitleInfo::GetTitleInfo(id);
	TitleInfo::GenerateTMD(ti->workingDir, ti->id);
	TitleInfo::GenerateTicket(ti);
	WriteLine("saved tmd & cetk to '[%s] %s'", ti->region, ti->name);
}

void vmcount(po::variables_map vm, po::options_description desc, std::string defaultdir)
{
	if (vm.count("help")) {
		cout << desc << endl;
	}

	if (vm.count("dl")) {
		downloadcontent(defaultdir, vm["dl"].as<string>());
	}

	if (vm.count("de")) {
		string contentDir(vm["de"].as<string>());
		simpleDecrypt(StringToCharArray(contentDir), defaultdir);
	}

	if (vm.count("tik")) {
		create_decrypt_file(vm["tik"].as<string>());
	}
}

int main(signed int argc, char* argv[])
{
	po::options_description desc = defineOptions();

	rang::setControlMode(rang::control::Auto);
	SetConsoleTitleA("MapleSeed Command Line");

	auto fsp = path((char*)argv[0]).normalize();
	auto dir = fsp.parent_path().generic_string();
	TitleInfo::outputDir = dir;

	struct stat buffer;
	if ((stat("tmd", &buffer) == 0) && (stat("cetk", &buffer) == 0)) {
		simpleDecrypt("./", dir);
		return getchar();
	}

	header();

	if (argc > 1) {
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
		vmcount(vm, desc, dir);
		return 0;
	}
	else {
		cout << desc << endl;
		while (true)
		{
			try {
				po::variables_map vm;
				vector<string> args = po::split_winmain(getUserInput());
				po::store(po::command_line_parser(args).options(desc).run(), vm);
				po::notify(vm);
				vmcount(vm, desc, dir);
			}
			catch (exception e) {
				WriteLineRed(e.what());
			}
		}
	}
}

