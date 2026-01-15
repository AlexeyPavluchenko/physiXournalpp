#include "CosineHandler.h"

#include <algorithm>  // for max
#include <cmath>      // for abs, pow, M_PI, cos

#include "control/Control.h"                       // for Control
#include "control/settings/Settings.h"             // for Settings
#include "control/tools/BaseShapeHandler.h"        // for BaseShapeHandler
#include "control/tools/SnapToGridInputHandler.h"  // for SnapToGridInputHan...
#include "model/Point.h"                           // for Point
#include "util/Assert.h"

CosineHandler::CosineHandler(Control* control, const PageRef& page, bool flipShift, bool flipControl):
        BaseShapeHandler(control, page, flipShift, flipControl) {}

CosineHandler::~CosineHandler() = default;

auto CosineHandler::createShape(bool isAltDown, bool isShiftDown, bool isControlDown)
        -> std::pair<std::vector<Point>, Range> {
    /**
     * Snap point to grid (if enabled - Alt key pressed will toggle)
     */
    Point c = snappingHandler.snapToGrid(this->currPoint, isAltDown);

    double width = c.x - this->startPoint.x;
    double height = c.y - this->startPoint.y;
    int periods = 3;


    this->modShift = isShiftDown;
    this->modControl = isControlDown;

    Settings* settings = control->getSettings();
    if (settings->getDrawDirModsEnabled()) {
        // change modifiers based on draw dir
        this->modifyModifiersByDrawDir(width, height, true);
    }

    if (this->modShift) {
        // make square
        width = (this->modControl) ? std::hypot(width, height) :
                                     std::copysign(std::max(std::abs(width), std::abs(height)), width);
        height = std::copysign(width, height);
    }

    double radiusX = 0.5 * width;
    double radiusY = 0.5 * height;
    double center_x = this->startPoint.x + radiusX;
    double center_y = this->startPoint.y + radiusY;
    double phase = 0;
    double amplitude = 0.5 * std::abs(height);
    double frequency = (std::abs(width) < 1e-6) ? 0 : (2.0 * M_PI * periods) / std::abs(width);
            
        

    if (!this->modControl) {
        // control key not down, draw cosine
        phase = 0;
    } else {
        // control key down, draw sine
        phase = -0.5 * M_PI;
    }

    /*
     * Set resolution depending on the width and height (heuristic)
     */
    auto nbPtsPerPeriod =
            static_cast<unsigned int>(std::ceil(5 + 0.3 * (std::abs(amplitude) + std::abs(width/periods))));
    const double stepPhase = (2.0 * M_PI) / nbPtsPerPeriod;
    std::pair<std::vector<Point>, Range> res;
    std::vector<Point>& shape = res.first;

    /*
     * This call to reserve() makes the calls to std::transform() below safe.
     * DO NOT REMOVE
     * .
     */
    shape.reserve(periods * nbPtsPerPeriod + 1);

    shape.emplace_back(center_x - radiusX, center_y -amplitude * std::cos(phase));
    for (unsigned int j = 1U; j <= periods * nbPtsPerPeriod; j++) {
        const double tgtPhase = stepPhase * j;
        double xp = center_x - radiusX + (static_cast<double>(j) / (periods * nbPtsPerPeriod)) * (2.0 * radiusX);
        double yp = center_y - amplitude * std::cos(tgtPhase + phase);
        shape.emplace_back(xp, yp);
    }
    // close the cosine shape
    Range rg(center_x + radiusX, center_y + radiusY);
    rg.addPoint(center_x - radiusX, center_y - radiusY);
    res.second = rg;

    return res;
}
