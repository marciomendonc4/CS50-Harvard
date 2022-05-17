void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pRed, pGreen, pBlue;
    float pAverage;

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            //Setting variables for easy access
            pBlue = image[i][j].rgbtBlue;
            pGreen = image[i][j].rgbtGreen;
            pRed = image[i][j].rgbtRed;

            pAverage = round((pBlue + pGreen + pRed) / 3.0);

            image[i][j].rgbtBlue = pAverage;
            image[i][j].rgbtGreen = pAverage;
            image[i][j].rgbtRed = pAverage;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float newBlue, newGreen, newRed;
    int pRed, pGreen, pBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Setting variables for easy access
            pBlue = image[i][j].rgbtBlue;
            pGreen = image[i][j].rgbtGreen;
            pRed = image[i][j].rgbtRed;

            newBlue = round(.272 * pRed + .534 * pGreen + .131 * pBlue);
            if (newBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = newBlue;
            }

            newGreen = round(.349 * pRed + .686 * pGreen + .168 * pBlue);
            if (newGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = newGreen;
            }

            newRed = round(.393 * pRed + .769 * pGreen + .189 * pBlue);
            if (newRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = newRed;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width; j++, k--)
        {
            if (width % 2 == 0)
            {
                if (j > k)
                {
                    break;
                }
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][k];
                image[i][k] = temp;
            }
            else
            {
                if (j == k)
                {
                    break;
                }
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][k];
                image[i][k] = temp;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    //creating a copy of the image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE p1 = imageCopy[i][j];
            RGBTRIPLE p2 = imageCopy[i][j + 1];
            RGBTRIPLE p3 = imageCopy[i][j - 1];
            RGBTRIPLE p4 = imageCopy[i + 1][j];
            RGBTRIPLE p5 = imageCopy[i + 1][j + 1];
            RGBTRIPLE p6 = imageCopy[i + 1][j - 1];
            RGBTRIPLE p7 = imageCopy[i - 1][j];
            RGBTRIPLE p8 = imageCopy[i - 1][j + 1];
            RGBTRIPLE p9 = imageCopy[i - 1][j - 1];

            //top left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p2.rgbtBlue + p5.rgbtBlue + p4.rgbtBlue) / 4.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p2.rgbtGreen + p5.rgbtGreen + p4.rgbtGreen) / 4.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p2.rgbtRed + p5.rgbtRed + p4.rgbtRed) / 4.0);
            }
            //top right corner
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p3.rgbtBlue + p6.rgbtBlue + p4.rgbtBlue) / 4.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p3.rgbtGreen + p6.rgbtGreen + p4.rgbtGreen) / 4.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p3.rgbtRed + p6.rgbtRed + p4.rgbtRed) / 4.0);
            }
            //bottom left corner
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p7.rgbtBlue + p8.rgbtBlue + p2.rgbtBlue) / 4.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p7.rgbtGreen + p8.rgbtGreen + p2.rgbtGreen) / 4.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p7.rgbtRed + p8.rgbtRed + p2.rgbtRed) / 4.0);
            }
            //bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p3.rgbtBlue + p9.rgbtBlue + p7.rgbtBlue) / 4.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p3.rgbtGreen + p9.rgbtGreen + p7.rgbtGreen) / 4.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p3.rgbtRed + p9.rgbtRed + p7.rgbtRed) / 4.0);
            }
            //top row
            else if (i == 0 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p3.rgbtBlue + p2.rgbtBlue + p6.rgbtBlue + p4.rgbtBlue + p5.rgbtBlue) / 6.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p3.rgbtGreen + p2.rgbtGreen + p6.rgbtGreen + p4.rgbtGreen + p5.rgbtGreen) / 6.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p3.rgbtRed + p2.rgbtRed + p6.rgbtRed + p4.rgbtRed + p5.rgbtRed) / 6.0);
                
            }
            //bottom row
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p3.rgbtBlue + p2.rgbtBlue + p9.rgbtBlue + p7.rgbtBlue + p8.rgbtBlue) / 6.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p3.rgbtGreen + p2.rgbtGreen + p9.rgbtGreen + p7.rgbtGreen + p8.rgbtGreen) / 6.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p3.rgbtRed + p2.rgbtRed + p9.rgbtRed + p7.rgbtRed + p8.rgbtRed) / 6.0);
            }
            //left edge
            else if (i > 0  && i < height - 1 && j == 0)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p7.rgbtBlue + p4.rgbtBlue + p8.rgbtBlue + p2.rgbtBlue + p5.rgbtBlue) / 6.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p7.rgbtGreen + p4.rgbtGreen + p8.rgbtGreen + p2.rgbtGreen + p5.rgbtGreen) / 6.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p7.rgbtRed + p4.rgbtRed + p8.rgbtRed + p2.rgbtRed + p5.rgbtRed) / 6.0);
            }
            //right edge
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p7.rgbtBlue + p4.rgbtBlue + p9.rgbtBlue + p3.rgbtBlue + p6.rgbtBlue) / 6.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p7.rgbtGreen + p4.rgbtGreen + p9.rgbtGreen + p3.rgbtGreen + p6.rgbtGreen) / 6.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p7.rgbtRed + p4.rgbtRed + p9.rgbtRed + p3.rgbtRed + p6.rgbtRed) / 6.0);
            }
            //middle
            else
            {
                image[i][j].rgbtBlue = round((p1.rgbtBlue + p2.rgbtBlue + p3.rgbtBlue + p4.rgbtBlue + p5.rgbtBlue + p6.rgbtBlue + p7.rgbtBlue + p8.rgbtBlue + p9.rgbtBlue) / 9.0);
                
                image[i][j].rgbtGreen = round((p1.rgbtGreen + p2.rgbtGreen + p3.rgbtGreen + p4.rgbtGreen + p5.rgbtGreen + p6.rgbtGreen + p7.rgbtGreen + p8.rgbtGreen + p9.rgbtGreen) / 9.0);
                
                image[i][j].rgbtRed = round((p1.rgbtRed + p2.rgbtRed + p3.rgbtRed + p4.rgbtRed + p5.rgbtRed + p6.rgbtRed + p7.rgbtRed + p8.rgbtRed + p9.rgbtRed) / 9.0);
            }
        }
    }
    
    
    return;
}