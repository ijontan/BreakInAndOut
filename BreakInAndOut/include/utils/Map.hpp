namespace Utils
{
	class Map
	{
	public:
		Map();
		~Map();

	private:
		std::vector<std::vector<int>> mapData; // Example: 2D vector to represent the map
	};

	Map::Map()
	{
	}

	Map::~Map()
	{
	}
}