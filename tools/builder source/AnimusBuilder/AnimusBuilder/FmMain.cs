using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace AnimusBuilder
{
    public partial class FmMain : Form
    {
        public FmMain()
        {
            InitializeComponent();
            FlpPool.DragEnter += PanelDragEnter;
            FlpHPins.DragEnter += PanelDragEnter;
            FlpVPins.DragEnter += PanelDragEnter;


            FlpPool.DragDrop += PanelDragDrop;
            FlpHPins.DragDrop += PanelDragDrop;
            FlpVPins.DragDrop += PanelDragDrop;
            
            MdSetting.LoadSettings();
            TbAnimusPath.Text = MdSetting.setting.animusPath;
            TbModPath.Text = MdSetting.setting.modPath;
            TbOutputPath.Text = MdSetting.setting.outputPath;

            //MdCore.Serialize<ClController>(ClController.ProMicro(), MdConstant.controllers + MdConstant.pseparator + "pro-micro.ukbct");
            MdCore.Serialize<ClBuildList>(ClBuildList.BuildAll(), MdConstant.root + MdConstant.pseparator + "build-all.ukbl");

        }

        private void FmMain_Load(object sender, EventArgs e)
        {

        }

        private void BtnMouseDown(object sender, MouseEventArgs e)
        {
            var btn = sender as Button;
            btn.DoDragDrop(btn, DragDropEffects.Move);
        }

        private void PanelDragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }

        private void PanelDragDrop(object sender, DragEventArgs e)
        {
            var btn = e.Data.GetData(typeof(Button)) as Button;
            var pnl = sender as Panel;
            if (btn.Parent == pnl)
            {
                btn.Parent = null;
            }
            btn.Parent = pnl;
        }

        private void TbAnimusPath_TextChanged(object sender, EventArgs e)
        {
            MdSetting.setting.animusPath = (sender as TextBox).Text;
            MdSetting.SaveSettings();
        }

        private void TbModPath_TextChanged(object sender, EventArgs e)
        {

            MdSetting.setting.modPath = (sender as TextBox).Text;
            MdSetting.SaveSettings();
            if (Directory.Exists(MdSetting.setting.modPath))
            {
                LbModPool.Items.Clear();
                LbMods.Items.Clear();
                LbModPool.Items.AddRange(Directory.GetDirectories(MdSetting.setting.modPath).ToList<string>().Select(str => Path.GetFileNameWithoutExtension(str)).ToArray());
            }

        }

        private void TbOutputPath_TextChanged(object sender, EventArgs e)
        {

            MdSetting.setting.outputPath = (sender as TextBox).Text;
            MdSetting.SaveSettings();
        }

        private void BtnSelectControl_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Controller File | " + MdConstant.eControllers;
            dialog.Title = "Select Controller";
            dialog.InitialDirectory = MdConstant.controllers;
            dialog.ShowDialog();
            if (dialog.FileName != "")
            {
                MdGlobal.selectedController = MdCore.Deserialize<ClController>(dialog.FileName);

            }
        }

        private void BtnLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Build Profile | " + MdConstant.eProfiles;
            dialog.Title = "Select Build Profile";
            dialog.InitialDirectory = MdConstant.profiles;
            dialog.ShowDialog();
            if (dialog.FileName != "")
            {
                BtnResetPins.PerformClick();
                BtnResetMod.PerformClick();
                ClBuildProfile bp = MdCore.Deserialize<ClBuildProfile>(dialog.FileName);
                List<string> pinpool = FlpPool.Controls.Cast<Button>().Select(btn => btn.Text).ToList();
                List<string> modpool = LbModPool.Items.Cast<string>().ToList();
                foreach (string str in bp.hpins)
                {
                    if (pinpool.Contains(str))
                    {
                        AddPin(str, FlpHPins);
                        RemovePin("bt_" + str, FlpPool);
                    }
                    else
                    {
                        MessageBox.Show("The current controller does not contain pin " + str + "\nWhich is part of the list of horizontal pins\nAs such it is not added to the hpin pool");
                    }
                }
                foreach (string str in bp.vpins)
                {
                    if (pinpool.Contains(str))
                    {
                        AddPin(str, FlpVPins);
                        RemovePin("bt_" + str, FlpPool);
                    }
                    else
                    {
                        MessageBox.Show("The current controller does not contain pin " + str + "\nWhich is part of the list of vertical pins\nAs such it is not added to the vpin pool");
                    }
                }

                foreach (string str in bp.mods)
                {
                    if (modpool.Contains(str))
                    {
                        LbMods.Items.Add(str);
                        LbModPool.Items.Remove(str);
                    }
                }


                TbBuild.Text = bp.driver_build;
                TbName.Text = bp.name;
                TbVariant.Text = bp.variant;
                NudRefresh.Value = Convert.ToDecimal(bp.refresh);
            }
        }

        private void UpdateProfile()
        {
            MdGlobal.profile.driver_build = TbBuild.Text;

            MdGlobal.profile.hpins = FlpHPins.Controls.Cast<Button>().Select(btn => btn.Text).ToList();
            MdGlobal.profile.vpins = FlpVPins.Controls.Cast<Button>().Select(btn => btn.Text).ToList();

            MdGlobal.profile.name = TbName.Text;
            MdGlobal.profile.refresh = NudRefresh.Value.ToString();
            MdGlobal.profile.variant = TbVariant.Text;
            MdGlobal.profile.mods = LbMods.Items.Cast<String>().ToList();
        }

        private void BtnSave_Click(object sender, EventArgs e)
        {
            UpdateProfile();


            SaveFileDialog dialog = new SaveFileDialog();
            dialog.Filter = "Build Profile | " + MdConstant.eProfiles;
            dialog.Title = "Save Build Profile";
            dialog.InitialDirectory = MdConstant.profiles;
            dialog.ShowDialog();
            if (dialog.FileName != "")
            {

                MdCore.Serialize<ClBuildProfile>(MdGlobal.profile, dialog.FileName);
            }
        }


        public void SetControllerName(string input)
        {
            LController.Text = input;
        }

        public void AddPin(string name, Control parent)
        {
            var btn = new Button();
            btn.Name = "bt_" + name;
            btn.Text = name;
            btn.Parent = parent;
            btn.Size = new Size(33, 33);
            btn.MouseDown += BtnMouseDown;
        }

        public void RemovePin(string name, Control parent)
        {
            foreach (Control ctrl in parent.Controls)
            {
                if (ctrl.Name == name)
                {
                    parent.Controls.Remove(ctrl);
                    break;
                }
            }
        }


        public void SetPins(List<string> input)
        {
            FlpHPins.Controls.Clear();
            FlpVPins.Controls.Clear();
            FlpPool.Controls.Clear();

            foreach(string element in input)
            {
                AddPin(element, FlpPool);
            }
        }

        private void BtnResetPins_Click(object sender, EventArgs e)
        {
            SetPins(MdGlobal.selectedController.pins);
        }

        private void BtAddMod_Click(object sender, EventArgs e)
        {
            if (LbModPool.SelectedItem != null)
            {
                LbMods.Items.Add(LbModPool.SelectedItem);
                LbModPool.Items.Remove(LbModPool.SelectedItem);
            }
        }


        private void BtnAnimusPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.Description = "Select the directory containing animus.ino";
            if (Directory.Exists(MdSetting.setting.animusPath))
            {
                dialog.SelectedPath = MdSetting.setting.animusPath;
            }
            else
            {
                dialog.SelectedPath = MdConstant.root;
            }
            dialog.ShowDialog();
            if (dialog.SelectedPath != "")
            {
                TbAnimusPath.Text = dialog.SelectedPath;
            }
        }

        private void BtnModPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.Description = "Select the directory containing the mods";
            if (Directory.Exists(MdSetting.setting.modPath))
            {
                dialog.SelectedPath = MdSetting.setting.modPath;
            }
            else
            {
                dialog.SelectedPath = MdConstant.root;
            }
            dialog.ShowDialog();
            if (dialog.SelectedPath != "")
            {
                TbModPath.Text = dialog.SelectedPath;
            }
        }

        private void BtnOutputPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.Description = "Select the directory for the output";
            if (Directory.Exists(MdSetting.setting.outputPath))
            {
                dialog.SelectedPath = MdSetting.setting.outputPath;
            }
            else
            {
                dialog.SelectedPath = MdConstant.root;
            }
            dialog.ShowDialog();
            if (dialog.SelectedPath != "")
            {
                TbOutputPath.Text = dialog.SelectedPath;
            }
        }

        private void BtnBuild_Click(object sender, EventArgs e)
        {
            UpdateProfile();
            MessageBox.Show(MdCore.BuildAnimus(MdGlobal.profile, MdGlobal.selectedController, MdSetting.setting.animusPath, MdSetting.setting.modPath, MdSetting.setting.outputPath));

        }

        public void SetMods(List<string> input)
        {
            LbMods.Items.Clear();

            LbModPool.Items.Clear();

            foreach (string element in input)
            {
                LbModPool.Items.Add(element);
            }
        }
        private void BtnResetMod_Click(object sender, EventArgs e)
        {
            SetMods(Directory.GetDirectories(MdSetting.setting.modPath).ToList<string>().Select(str => Path.GetFileNameWithoutExtension(str)).ToList());
        }

    }
}
