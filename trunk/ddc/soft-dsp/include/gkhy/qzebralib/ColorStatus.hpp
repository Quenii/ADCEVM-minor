#include "gkhy/qzebralib/qzebra_lib_global.hpp"
#include "gkhy/qzebralib/ColorStyle.hpp"

namespace gkhy
{
	namespace QZebraLib
	{
		template <typename T>
		class ColorStatus
		{
		public:
			enum StatusType
			{				
				StatusDisabled,
				StatusFunctions,

				StatusDisonnected,
				StatusConnecting,
				StatusConnected,
				
				StatusSearch,
				StatusCheck,
				StatusAcquisition,

				StatusUnlocked,
				StatusLocked,

				StatusAlarm,
				StatusOkay
			};

			enum CommandType
			{
				CommandConfig,
				CommandApply,
			};

		public:
			ColorStatus(T* widget) : widgetPtr(widget) {} 
			virtual ~ColorStatus() {}
		private:
			Q_DISABLE_COPY(ColorStatus)

		public:
			void setStatus(StatusType status)
			{
				switch (status)
				{
				case StatusDisabled:
					widgetPtr->setText(QWidget::tr("Disabled"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Red);
					break;

				case StatusFunctions:
					widgetPtr->setText(QWidget::tr("Functions"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Green);
					break;

				case StatusDisonnected:
					widgetPtr->setText(QWidget::tr("Disconnected"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Red);
					break;

				case StatusConnecting:
					widgetPtr->setText(QWidget::tr("Connecting"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Yellow);
					break;

				case StatusConnected:
					widgetPtr->setText(QWidget::tr("Connected"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Green);
					break;

				case StatusAlarm:
					widgetPtr->setText(QWidget::tr("Alarm"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Yellow);
					break;

				case StatusSearch:
					widgetPtr->setText(QWidget::tr("Search"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Yellow);
					break;

				case StatusCheck:
					widgetPtr->setText(QWidget::tr("Check"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Yellow);
					break;

				case StatusAcquisition:
					widgetPtr->setText(QWidget::tr("Acquisition"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Yellow);
					break;

				case StatusUnlocked:
					widgetPtr->setText(QWidget::tr("Unlocked"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Red);
					break;

				case StatusLocked:
					widgetPtr->setText(QWidget::tr("Locked"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Green);
					break;

				case StatusOkay:
					widgetPtr->setText(QWidget::tr("Okay"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Green);
					break;

				default:
					break;
				}			
			}

			void setStatus(CommandType command)
			{
				switch (command)
				{
				case CommandConfig:
					widgetPtr->setText(QWidget::tr("Config"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Normal);
					break;

				case CommandApply:
					widgetPtr->setText(QWidget::tr("Apply"));
					ColorStyle(widgetPtr).setStyle(ColorStyle::Yellow);
					break;

				default:
					break;
				}
			}

		private:
			T* widgetPtr;
		};
	}
}