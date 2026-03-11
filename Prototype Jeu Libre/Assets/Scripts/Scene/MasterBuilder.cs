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
    [SerializeField] private GameObject[] buildingVariants; // Array of different building prefabs
    [SerializeField] private float3[] buildingScales; // Array of different building prefabs


    /// TOOLS


    /// METHODS

    public GameObject GetRandomBuilding()
    {
        int randomIndex = UnityEngine.Random.Range(0, buildingVariants.Length);
        return buildingVariants[randomIndex];
    }

    public Tuple<GameObject, float3> GetRandomBuildingWithScale()
    {
        int randomIndex = UnityEngine.Random.Range(0, buildingVariants.Length);
        return new Tuple<GameObject, float3>(buildingVariants[randomIndex], buildingScales[randomIndex]);
    }

    public Tuple<GameObject, float3> GetBuilding(int index)
    {
        if (index < buildingVariants.Length)
            return new Tuple<GameObject, float3>(buildingVariants[index], buildingScales[index]);
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
