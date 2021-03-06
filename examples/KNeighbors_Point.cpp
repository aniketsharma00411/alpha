// import header files
#include <KNeighborsClassifier.hpp>
#include <matplotlibcpp.hpp>
#include <model_selection.hpp>
namespace plt = matplotlibcpp;

// Example program

// Read csv files to get a Matrix object.
// Slice the Matrix object to a suitable size.
// Plot known data points
// Run KNeighborsClustering and predict the cluster label for a point
// Print score and plot necessary graphs

int main() {

    // Specify backend renderer for matplotlib
    plt::backend("GTK3Agg");

    // create dataset with two feature
    Matrix mat = read_csv("./datasets/blobs/blobs.csv");
    Matrix X = mat.slice(5, 10, 0, 2);
    Matrix Y = mat.slice(5, 10, 2, 3);
    X.to_double();
    Y.to_double();

    // Split the data and targets into training/testing sets
    auto [X_train, X_test, Y_train, Y_test] = model_selection.train_test_split(X, Y, 0);

    // plot training dataset
    plt::figure_size(800, 600);
    plt::title("KNeighbors Known Dataset (Red, Green, Blue) with Unknown Point (Margenta)");
    plt::plot(matrix.slice_select(X_train, Y_train, 0.0, 0).get_col(0),
              matrix.slice_select(X_train, Y_train, 0.0, 1).get_col(0), "ro");
    plt::plot(matrix.slice_select(X_train, Y_train, 1.0, 0).get_col(0),
              matrix.slice_select(X_train, Y_train, 1.0, 1).get_col(0), "g^");
    plt::plot(matrix.slice_select(X_train, Y_train, 2.0, 0).get_col(0),
              matrix.slice_select(X_train, Y_train, 2.0, 1).get_col(0), "bD");

    // create KMeans object with k as parameters
    KNeighborsClassifier knn(0);
    knn.fit(X_train, Y_train);
    std::cout << "K Neighbors Clustering Algorithm: " << std::endl;
    std::cout << "Testing against different values of K KNeighbors: " << std::endl;

    // Identifying the cluster label for a point P = (x, y);
    std::vector<double> P = {-1.1819949309545112, 3.568805376115622};
    std::vector<double> Px = {-1.1819949309545112};
    std::vector<double> Py = {3.568805376115622};
    plt::plot(Px, Py, "ms");
    plt::save("./build/plots/KNeighbors Point Known Dataset.png");
    plt::show();
    for (int i = 1; i < 4; i++) {
        knn.set_params(i);
        Matrix label = knn.kneighbors(P);
        std::cout << "For K = " << i << " : ";

        // plot training dataset
        plt::figure_size(800, 600);
        plt::named_plot("Known Red", matrix.slice_select(X_train, Y_train, 0.0, 0).get_col(0),
                        matrix.slice_select(X_train, Y_train, 0.0, 1).get_col(0), "ro");
        plt::named_plot("Known Green", matrix.slice_select(X_train, Y_train, 1.0, 0).get_col(0),
                        matrix.slice_select(X_train, Y_train, 1.0, 1).get_col(0), "g^");
        plt::named_plot("Known Blue", matrix.slice_select(X_train, Y_train, 2.0, 0).get_col(0),
                        matrix.slice_select(X_train, Y_train, 2.0, 1).get_col(0), "bD");
        switch ((int)label(0, 0)) {
        case 0:
            std::cout << "Red" << std::endl;
            plt::title(
                "KNeighbors Known Dataset (Red, Green, Blue) with Unknown Point predicted (Red)");
            plt::named_plot("Predicted red", Px, Py, "rP");
            plt::legend();
            plt::save("./build/plots/KNeighbors Point Known Dataset-Red.png");
            plt::show();
            break;
        case 1:
            std::cout << "Green" << std::endl;
            plt::title(
                "KNeighbors Known Dataset (Red, Green, Blue) with Unknown Point predicted (Green)");
            plt::named_plot("Predicted green", Px, Py, "gP");
            plt::legend();
            plt::save("./build/plots/KNeighbors Point Known Dataset-Green.png");
            plt::show();
            break;
        case 2:
            std::cout << "Blue" << std::endl;
            plt::title(
                "KNeighbors Known Dataset (Red, Green, Blue) with Unknown Point predicted (Blue)");
            plt::named_plot("Predicted blue", Px, Py, "bP");
            plt::legend();
            plt::save("./build/plots/KNeighbors Point Known Dataset-Blue.png");
            plt::show();
            break;
        }
    }

    return 0;
}
