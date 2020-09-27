#ifndef LINEGRID_H
#define LINEGRID_H

#include "display.h"

class LineGrid : public sf::Drawable, public sf::Transformable
{
	public:

	/* brief:	Add a series of coordinates to vertex array corresponding to a line grid.
	   param:	Dim, the width/height of each square.
	   returns:	True if successful.
	*/
	bool create(int dim)
	{
		int row_num = (WINDOW_H+1)/dim;	// Calculate number of rows required.
		int col_num = (WINDOW_W+1)/dim;	// Calculate number of columns required.

		m_vertices.setPrimitiveType(sf::Lines);
		m_vertices.resize((row_num + col_num) * 2);

		// Create vertical lines.
		for (int i = 0; i < col_num; i++)
		{
			sf::Vertex* line = &m_vertices[i * 2];
		
			// Define each side of line.
			line[0].position = sf::Vector2f(i * dim, 0);
			line[1].position = sf::Vector2f(i * dim, WINDOW_H);
		}

		// Create horizontal lines.
		for (int j = 0; j < row_num; j++)
		{
			sf::Vertex* line = &m_vertices[(col_num * 2) + (j * 2)];

			line[0].position = sf::Vector2f(0, j * dim);
			line[1].position = sf::Vector2f(WINDOW_W, j * dim);
		}

		return true;
	}

	private:

	// Draw function.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    	{
        	// Apply the transform.
        	states.transform *= getTransform();

        	// Draw the vertex array.
        	target.draw(m_vertices, states);
    	}

	// Private variables.
	sf::VertexArray m_vertices;
};

#endif
