#include "FileHelper.h"
#include "qdebug.h"

FileHelper::FileHelper()
{

}

FileHelper::~FileHelper()
{

}

bool FileHelper::createDirectory(std::string path)
{
	try
	{
		return boost::filesystem::create_directory(path);
	}
	catch (std::exception& e)
	{
		qDebug() << "[ Exception ] >>" << e.what();
	}

	return false;
}


bool FileHelper::copyFile(std::string filePath, std::string desPath)
{
	try
	{
		boost::filesystem::copy_file(filePath, desPath, boost::filesystem::copy_option::overwrite_if_exists);
		return true;

	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		qDebug() << "[ Exception ] >>" << e.what();
	}

	return false;
}

bool FileHelper::deleteFile(std::string path)
{
	try
	{
		boost::filesystem::remove_all(path);
		return true;

	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		qDebug() << "[ Exception ] >>" << e.what();
	}

	return false;
}

bool FileHelper::exists(std::string path)
{
	return boost::filesystem::exists(path);
}

void FileHelper::writeXML(Patient* patient)
{
	boost::property_tree::ptree tree;

	tree.put("name", patient->name);
	tree.put("sex", patient->sex);
	tree.put("folders", "");

	for (Model* folder : patient->list_folder )
	{
		tree.add("folders.folder", folder->name);
	}

	boost::property_tree::write_xml( patient->location + "/patient.lia" , tree);

}

void FileHelper::writeXML(Folder* folder)
{
	boost::property_tree::ptree tree;

	tree.put("name", folder->name);
	tree.put("type", folder->type);
	tree.put("images", "");

	for ( Model* image : folder->list_dataImage )
	{
		tree.add("images.image", image->name);
	}

	boost::property_tree::write_xml(folder->location + "/folder.lia", tree);

}

void FileHelper::writeXML(DataImage* image)
{
	boost::property_tree::ptree tree;

	tree.put("name", image->name);
	tree.put("type", image->type);
	tree.put("note", image->note);
	tree.put("options", "");

	Message msg_opt = image->option->getMessage();
	for (auto const &it : msg_opt)
	{
		tree.put("options." + it.first, it.second );
	}

	boost::property_tree::write_xml(image->location + "/image.lia", tree);

}

Message FileHelper::readFolderXML(std::string path)
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_xml(path + "/folder.lia", tree);

	Message msg;
	msg["name"] = tree.get<std::string>("name");
	msg["type"] = tree.get<std::string>("type");
	msg["location"] = path;

	int num = 0;

	for (boost::property_tree::ptree::value_type &v : tree.get_child("images"))
	{
		num++;
		msg["image" + std::to_string(num)] = v.second.data();
	}

	return msg;
}

Message FileHelper::readImageXML(std::string path)
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_xml(path + "/image.lia", tree);

	Message msg;
	msg["name"] = tree.get<std::string>("name");
	msg["type"] = tree.get<std::string>("type");
	msg["note"] = tree.get<std::string>("note");
	msg["location"] = path;

	for (boost::property_tree::ptree::value_type &v : tree.get_child("options"))
	{
		msg[v.first.data()] = v.second.data();
	}

	return msg;
}

Message FileHelper::readXML(std::string path)
{
	boost::property_tree::ptree tree;
	boost::property_tree::read_xml( path + "/patient.lia" , tree );

	Message msg;
	msg["name"] = tree.get<std::string>("name");
	msg["sex"] = tree.get<std::string>("sex");
	msg["location"] = path;

	int num = 0;

	for (boost::property_tree::ptree::value_type &v : tree.get_child("folders"))
	{
		std::string k = v.first.data();
		if ( k == "folder" )
		{
			qDebug() << v.second.data().c_str();
			num++;
			msg["folder" + std::to_string(num)] = v.second.data();
		}
	}

	return msg;
}
