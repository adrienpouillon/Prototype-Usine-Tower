using System;
using Unity.Mathematics;
using UnityEngine;

public class MasterBuilder : MonoBehaviour
{
    /// <SINGLETON>
    public static MasterBuilder Instance { get; private set; }
    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this.gameObject);
            return;
        }
        Instance = this;
    }
    /// <SINGLETON>

    // BUILDING VARIANTS
    [Header("Conveyor")]
    [SerializeField] private GameObject[] conveyorVariants; // Array of different building prefabs
    [SerializeField] private float3[] conveyorScales; // Array of different building prefabs
    [Header("General")]
    [SerializeField] private GameObject[] generalVariants; // Array of different building prefabs
    [SerializeField] private float3[] generalScales; // Array of different building prefabs
    [Header("Armory")]
    [SerializeField] private GameObject[] armoryVariants; // Array of different building prefabs
    [SerializeField] private float3[] armoryScales; // Array of different building prefabs
    [Header("Turret")]
    [SerializeField] private GameObject[] turretVariants; // Array of different building prefabs
    [SerializeField] private float3[] turretScales; // Array of different building prefabs


    /// TOOLS


    /// METHODS
    public Tuple<GameObject, float3> GetConveyor(int index)
    {
        if (index < conveyorVariants.Length)
            return new Tuple<GameObject, float3>(conveyorVariants[index], conveyorScales[index]);
        return null;
    }
    public Tuple<GameObject, float3> GetGeneral(int index)
    {
        if (index < generalVariants.Length)
            return new Tuple<GameObject, float3>(generalVariants[index], generalScales[index]);
        return null;
    }
    public Tuple<GameObject, float3> GetArmory(int index)
    {
        if (index < armoryVariants.Length)
            return new Tuple<GameObject, float3>(armoryVariants[index], armoryScales[index]);
        return null;
    }
    public Tuple<GameObject, float3> GetTurret(int index)
    {
        if (index < turretVariants.Length)
            return new Tuple<GameObject, float3>(turretVariants[index], turretScales[index]);
        return null;
    }

    public void SetMaterial(GameObject building, Material newMaterial)
    {
        if(building == null)
        {
            Debug.Log("MasterBuilder: SetMaterial - building is null");
            return;
        }
        MeshRenderer[] renderers = building.GetComponentsInChildren<MeshRenderer>();
        foreach (var renderer in renderers)
        {
            renderer.material = newMaterial;
        }
    }

    public void SetMaterial(GameObject building, Material[] newMaterial)
    {
        if(building == null)
        {
            Debug.Log("MasterBuilder: SetMaterials - building is null");
            return;
        }

        MeshRenderer[] renderers = building.GetComponentsInChildren<MeshRenderer>();

        if(renderers.Length != newMaterial.Length)
        {
            Debug.Log("MasterBuilder: SetMaterials - renderers length does not match newMaterial length");
            return;
        }

        for (int i = 0; i < renderers.Length; i++)
        {
            renderers[i].material = newMaterial[i];
        }
    }

    public Material[] GetMaterials(GameObject building)
    {
        MeshRenderer[] renderers = building.GetComponentsInChildren<MeshRenderer>();
        Material[] materials = new Material[renderers.Length];
        for (int i = 0; i < renderers.Length; i++)
        {
            materials[i] = renderers[i].material;
        }
        return materials;
    }

    public void EnableScripts(GameObject building)
    {
        MonoBehaviour[] scripts = building.GetComponentsInChildren<MonoBehaviour>();
        foreach (var s in scripts) s.enabled = true;
    }

    public void DisableScripts(GameObject building)
    {
        MonoBehaviour[] scripts = building.GetComponentsInChildren<MonoBehaviour>();
        foreach (var s in scripts) s.enabled = false;
    }
}
