#include "../../../../Utils/Util.h"

#include <numeric>

// Abbadon all hope ye who enter here.

enum class entrytype_t
{
	directory,
	file
};

struct entry_t
{
	std::string name;
	entrytype_t type;
	int32_t size;
	entry_t* parent;
	std::vector<entry_t*> children; // Only for directories
};

entry_t* new_entry(const std::string& name, entrytype_t type, entry_t* parent)
{
	entry_t* temp = new entry_t;
	temp->name = name;
	temp->parent = parent;
	temp->size = 0;
	temp->type = type;
	if(type == entrytype_t::directory)
		temp->children = std::vector<entry_t*>();

	return temp;
}

void calculate_directory_sizes(entry_t* root)
{
	if(root->children.empty()) { return; }

	for(entry_t* c : root->children)
	{
		calculate_directory_sizes(c);

		root->size += c->size;
	}
}

void traverse(const entry_t* parent, std::vector<int32_t>& out)
{
	for(const entry_t* dir : parent->children)
	{
		if(dir->type == entrytype_t::directory)
		{
			traverse(dir, out);
			if(dir->size <= 100000)
			{
				out.push_back(dir->size);
				continue;
			}
		}
	}

}

std::vector<int32_t> get_directories(const entry_t* root)
{
	std::vector<int32_t> dirs;
	traverse(root, dirs);
	return dirs;
}

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', true);

	entry_t* root = new_entry("/", entrytype_t::directory, nullptr);
	entry_t* current_node = root;
	size_t line_index = 0;
	while (line_index < lines.size())
	{
		const auto line = lines[line_index];
		const auto line_tokens = create_vector(line, "\\s+");
		const auto id_token = line_tokens[0];

		if (id_token == "$")
		{
			const auto command_token = line_tokens[1];
			if (command_token == "cd")
			{
				const auto destination = line_tokens[2];
				if(destination == "/")
				{
					current_node = root;
				}
				else if(destination == "..")
				{
					current_node = current_node->parent;
				}
				else
				{
					const auto search_name = line_tokens[2];
					const auto children = current_node->children;
					// TODO: CLEANUP
					bool found = false;
					for (entry_t* child : children)
					{
						if(child->name == search_name)
						{
							current_node = child;
							found = true;
							break;
						}
					}
					if(found) { line_index++; continue; }
					// TODO: END CLEANUP
				}
				line_index++;
				continue;
			}
			else if (command_token == "ls")
			{
				line_index++;
				continue;
			}
		}

		// Previous command was to list files.
		const auto entry_name = line_tokens[1];
		const auto entry_type = is_number(line_tokens[0]) ? entrytype_t::file : entrytype_t::directory;
		const auto entry_size = entry_type == entrytype_t::file ? to_number(id_token) : 0;
		entry_t* entry = new_entry(entry_name, entry_type, current_node);
		entry->size = entry_size;
		current_node->children.push_back(entry);

		line_index++;
	}

	Timer timer;
	calculate_directory_sizes(root);
	auto dir_sizes = get_directories(root);
	int32_t sum = std::accumulate(dir_sizes.begin(), dir_sizes.end(), 0);

	PRINT(sum);

	return 0;
}
