#include "CoordinateSystemHandler.h"

#include <algorithm>  // for max

#include "control/Control.h"                       // for Control
#include "control/settings/Settings.h"             // for Settings
#include "control/tools/BaseShapeHandler.h"        // for BaseShapeHandler
#include "control/tools/SnapToGridInputHandler.h"  // for SnapToGridInputHan...
#include "gui/XournalView.h"                       // for XournalView
#include "gui/inputdevices/PositionInputData.h"    // for PositionInputData
#include "model/Point.h"                           // for Point

CoordinateSystemHandler::CoordinateSystemHandler(Control* control, const PageRef& page, bool flipShift,
                                                 bool flipControl):
        BaseShapeHandler(control, page, flipShift, flipControl) {}

CoordinateSystemHandler::~CoordinateSystemHandler() = default;

/**
 * Draw a Cartesian coordinate system.
 *
 * @param currentPoint The current point the mouse cursor is pointing to.
 * @param shiftDown Boolean to indicate if "shift" is currently pressed.
 *                  It is currently not used.
 */
auto CoordinateSystemHandler::createShape(bool isAltDown, bool isShiftDown, bool isControlDown)
        -> std::pair<std::vector<Point>, Range> {
    /**
     * Snap point to grid (if enabled)
     */
    Point c = snappingHandler.snapToGrid(this->currPoint, isAltDown);

    double width = c.x - this->startPoint.x;
    double height = c.y - this->startPoint.y;
    int signW = width > 0 ? 1 : -1;
    int signH = height > 0 ? 1 : -1;
    const double thickness = control->getToolHandler()->getThickness();
    const double slimnessW = width / thickness;
    const double slimnessH = height / thickness;

    this->modShift = isShiftDown;
    this->modControl = isControlDown;

    Settings* settings = control->getSettings();
    if (settings->getDrawDirModsEnabled()) {
        // change modifiers based on draw dir
        this->modifyModifiersByDrawDir(width, height, true);
    }

    if (this->modShift) {
        // make square

        width = std::max(width * signW, height * signH) * signW;
        height = (width * signW) * signH;
    }

    const Point& p1 = this->startPoint;

    Range rg(p1.x, p1.y);
    rg.addPoint(p1.x + width, p1.y + height);


    // an appropriate opening angle 2*delta is Pi/3 radians for an arrow shape
    double delta = M_PI / 15.0;
    // We use different slimness regimes for proper sizing:
    const double THICK1 = 7, THICK3 = 1.6;
    const double LENGTH2 = 0.4, LENGTH4 = 0.8;
    // set up the size of the arrow head to be THICK1 x the thickness of the horizontal line
    double arrowDistW = thickness * THICK1;
    // but not too large compared to the line length
    if (slimnessW < THICK1 / LENGTH2) {
        // no arrow
        arrowDistW = 0;
    }
    // set up the size of the arrow head to be THICK1 x the thickness of the vertical line
    double arrowDistH = thickness * THICK1;
    // but not too large compared to the line length
    if (slimnessH < THICK1 / LENGTH2) {
        // no arrow
        arrowDistH = 0;
    }

    std::pair<std::vector<Point>, Range> res; // members initialised below
    std::vector<Point>& shape = res.first;

    int numPoints = 3;

    if (signW > 0 && arrowDistW != 0) {
        numPoints += 4;
    } else {
        arrowDistW = 0;
    }
    if (signH > 0 && arrowDistH != 0) {
        numPoints += 4;
    } else {
        arrowDistH = 0;
    }

    shape.reserve(numPoints);

    if (!this->modControl) {
        shape.emplace_back(p1.x, p1.y);
        if (arrowDistH != 0) {
            shape.emplace_back(p1.x - arrowDistH * cos(M_PI / 2 + delta), p1.y + arrowDistH * sin(M_PI / 2 + delta));
            shape.emplace_back(p1.x, p1.y);
            shape.emplace_back(p1.x - arrowDistH * cos(M_PI / 2 - delta), p1.y + arrowDistH * sin(M_PI / 2 - delta));
            shape.emplace_back(p1.x, p1.y);
        }
        shape.emplace_back(p1.x, p1.y + height);
        shape.emplace_back(p1.x + width, p1.y + height);
        if (arrowDistW != 0) {
            shape.emplace_back(p1.x + width - arrowDistW * cos(delta), p1.y + height - arrowDistW * sin(delta));
            shape.emplace_back(p1.x + width, p1.y + height);
            shape.emplace_back(p1.x + width - arrowDistW * cos(0 - delta), p1.y + height - arrowDistW * sin(0 - delta));
            shape.emplace_back(p1.x + width, p1.y + height);
        }
    } else {
        // Control is down, no arrows
        arrowDistH = 0;
        arrowDistW = 0;
        shape.emplace_back(p1.x, p1.y + height);
        if (arrowDistH != 0) {
            shape.emplace_back(p1.x - arrowDistH * cos(M_PI / 2 + delta), p1.y + height + arrowDistH * sin(M_PI / 2 + delta));
            shape.emplace_back(p1.x, p1.y + height);
            shape.emplace_back(p1.x - arrowDistH * cos(M_PI / 2 - delta), p1.y + height + arrowDistH * sin(M_PI / 2 - delta));
            shape.emplace_back(p1.x, p1.y + height);
        }
        shape.emplace_back(p1.x, p1.y);
        shape.emplace_back(p1.x + width, p1.y);
        if (arrowDistW != 0) {
            shape.emplace_back(p1.x + width - arrowDistW * cos(delta), p1.y - arrowDistW * sin(delta));
            shape.emplace_back(p1.x + width, p1.y);
            shape.emplace_back(p1.x + width - arrowDistW * cos(0 - delta), p1.y - arrowDistW * sin(0 - delta));
            shape.emplace_back(p1.x + width, p1.y);
        }
    }

    auto [minX, maxX] = std::minmax_element(shape.begin(), shape.end(), [](auto& p, auto& q) { return p.x < q.x; });
    auto [minY, maxY] = std::minmax_element(shape.begin(), shape.end(), [](auto& p, auto& q) { return p.y < q.y; });
    res.second = Range(minX->x, minY->y, maxX->x, maxY->y);

    return res;
}