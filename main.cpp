#include <bits/stdc++.h>
#include <filesystem>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <conio.h>

using namespace std;
using namespace std::filesystem;

string perms_linux(perms p){
	ostringstream ss;
	ss << ((p & perms::owner_read) != perms::none ? "r" : "-")
		<< ((p & perms::owner_write) != perms::none ? "w" : "-")
		<< ((p & perms::owner_exec) != perms::none ? "x" : "-")
		<< ((p & perms::group_read) != perms::none ? "r" : "-")
		<< ((p & perms::group_write) != perms::none ? "w" : "-")
		<< ((p & perms::group_exec) != perms::none ? "x" : "-")
		<< ((p & perms::others_read) != perms::none ? "r" : "-")
		<< ((p & perms::others_write) != perms::none ? "w" : "-")
		<< ((p & perms::others_exec) != perms::none ? "x" : "-");
	return ss.str();
}

string file_size(double size) {
	ostringstream ss;
	string PreFix = "B";
	if (size > 1000) {
		size /= 1000;
		PreFix = "KB";
	} if (size > 1000) {
		size /= 1000;
		PreFix = "MB";
	} if (size > 1000) {
		size /= 1000;
		PreFix = "GB";
	} if (size > 1000) {
		size /= 1000;
		PreFix = "TB";
	}
	ss.precision(2);
	ss << fixed << size << " " << PreFix;
	return ss.str();
}

void print_entry(path p) {
	directory_entry d(p);
	ostringstream out;
	struct stat fileStat;

	out << d.path().filename().c_str() << string(24 - out.str().length(), ' ');

	if (!d.is_directory())
		out << file_size(d.file_size());

	out << string(40 - out.str().length(), ' ')
		<< ((d.is_directory()) ? 'd' : '-')
		<< perms_linux(d.status().permissions()) << "\t";

	stat(d.path().filename().c_str(), &fileStat);
	auto pw = getpwuid(fileStat.st_uid);
	auto gp = getgrgid(fileStat.st_gid);

	out << pw->pw_name << "\t" << gp->gr_name << "\t"
		<< ctime(&fileStat.st_mtime) << " ";

	cout << out.str();
}

void print_files(path p) {
	directory_iterator d_itr(p);
	cout << "File Name\t\tFile Size\tPermission" << endl;
	cout << string(120,'-') << endl;
	directory_entry d(p), D(p.parent_path());
	print_entry(path("."));
	print_entry(path(".."));
	for (auto &e : d_itr) {
		print_entry(e.path());
	}
}

int main(){
	path p = current_path();
	print_files(p);
}